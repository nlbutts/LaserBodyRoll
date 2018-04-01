
#include <embedded/memory/NVSection.h>
#include <embedded/utility/checksum/fletcher/Fletcher.h>
#include <cstring>

namespace Embedded {
namespace Memory {

namespace FletcherChk=Utility::Checksum::Fletcher;

NVSection::NVSection(uint32_t nvBaseAddress, void* data, const void* defaultData, uint16_t dataSize, uint8_t numBlocks, IMemory &serialFlash)
: _nvBaseAddress(nvBaseAddress)
, _data(data)
, _defaultData(defaultData)
, _dataSize(dataSize)
, _numBlocks(numBlocks)
, _serialFlash(&serialFlash)
, _pageSize(_serialFlash->getPageSize())
, _minEraseSize(_serialFlash->getMinEraseSize())
, _currentBlock(0)
, _tag(0)
, _writeState(IDLE)
, _bytesWritten(0)
, _writeAddress(0)
, _dataChanged(false)
{
}

NVSection::~NVSection()
{
    _data = NULL;
    _defaultData = NULL;
    _serialFlash = NULL;
}

NVSection::NVSectionStatus NVSection::save()
{
    uint8_t pageWrite[_pageSize];
    memset(pageWrite, 0xFF, sizeof(pageWrite));

    if (!_serialFlash->isBusy())
    {
        switch (_writeState)
        {
            case IDLE:
            case SUCCESS:
            case FAILURE:
                _currentBlock++;
                if (_currentBlock >= _numBlocks)
                {
                    _currentBlock = 0;
                }
                _writeAddress = calculateBlockAddress(_currentBlock);
                _serialFlash->eraseSubsectorPoll(_writeAddress);
                _writeState = ERASE_FIRST_SUBSECTOR;
                break;

            case ERASE_FIRST_SUBSECTOR:
                _tag++;
                if (_tag == 0)
                {
                    _tag++;
                }
                pageWrite[TAG_OFFSET]           = _tag;
                pageWrite[DATASIZE_LSB_OFFSET]  = (_dataSize     ) & 0xFF;
                pageWrite[DATASIZE_MSB_OFFSET]  = (_dataSize >> 8) & 0xFF;

                FletcherChk::ChecksumType checksumA;
                FletcherChk::ChecksumType checksumB;
                FletcherChk::initialize<FletcherChk::Zero>(&checksumA, &checksumB);

                FletcherChk::calculate<FletcherChk::Zero>(_tag,                   &checksumA, &checksumB);
                FletcherChk::calculate<FletcherChk::Zero>((_dataSize & 0xFF),     &checksumA, &checksumB);
                FletcherChk::calculate<FletcherChk::Zero>((_dataSize >> 8) & 0xFF,&checksumA, &checksumB);
                FletcherChk::calculate<FletcherChk::Zero>(static_cast<uint8_t*>(_data), _dataSize, &checksumA, &checksumB);

                pageWrite[CHECKSUM_LSB_OFFSET]  = checksumA & 0xFF;
                pageWrite[CHECKSUM_MSB_OFFSET]  = checksumB & 0xFF;

                _bytesWritten = _pageSize - static_cast<uint16_t>(DATA_OFFSET);

                memcpy(&pageWrite[DATA_OFFSET], _data, _bytesWritten);
                _serialFlash->writeDataPoll(_writeAddress , pageWrite, _pageSize);
                _writeAddress += _pageSize;
                _writeState = PROCESSING;
                break;

            case PROCESSING:
                if ((_writeAddress & (_minEraseSize - 1)) == 0)
                {
                    _serialFlash->eraseSubsectorPoll(_writeAddress);
                    _writeState = ERASING;
                    break;
                }
                // lint -e616

            /* FALLTHROUGH */
            case ERASING:
                if(_bytesWritten >= _dataSize)
                {
                    //printknl("eepromSaveDataLazy Write complete");
                    _writeState = SUCCESS;
                    _dataChanged = false;
                }
                else
                {
                    uint8_t * dataPtr = static_cast<uint8_t*>(_data);
                    for (uint16_t index = 0; (index < _pageSize) && (_bytesWritten < _dataSize); ++index)
                    {
                        // This will be accessing beyond the ee array, but that is ok, the data will not be used in the checksum
                        pageWrite[index] = dataPtr[_bytesWritten++];
                    }
                    _serialFlash->writeDataPoll(_writeAddress, pageWrite, _pageSize);
                    _writeAddress += _pageSize;
                    _writeState = PROCESSING;
                }
                break;
            default:
                break;
        }
    }

    return _writeState;
}

NVSection::NVSectionStatus NVSection::load()
{
    uint16_t address = 0;
    uint8_t localTag = 0;
    bool  foundFirstTag = false;
    uint8_t blockIndex = 0;
    NVSection::NVSectionStatus status = FAILURE;

    _tag = 0;
    for (blockIndex = 0; blockIndex < _numBlocks; blockIndex++)
    {
        address = calculateBlockAddress(blockIndex);
        localTag = verifyBlock(address);
        if (localTag != 0)
        {
            int16_t diff = static_cast<int16_t>(localTag) - static_cast<int16_t>(_tag);

            if (!foundFirstTag)
            {
                _tag = localTag;
                _currentBlock = blockIndex;
                foundFirstTag = true;
            }

            if ((diff < -128))
            {
                _tag = localTag;
                _currentBlock = blockIndex;
            }
            else if ((localTag > _tag) && (diff <= 3))
            {
                _tag = localTag;
                _currentBlock = blockIndex;
            }
        }
        //LogDebug("Block=%d  ltag=%d  gtag=%d\r\n", (int32_t)blockIndex, (int32_t)localTag, (int32_t)_tag);
    }

    // We have a known good, tag, load that data into the structure
    if (_tag != 0)
    {
        /* load data into memory */
        address = calculateBlockAddress(_currentBlock);

        //read 3 times to be sure separate block serial flash read call happens
        for (int x = 0; x < 3; ++x)
        {
            if (verifyBlock(address))
            {
                status = SUCCESS;
                break;
            }
        }
    }
    if (status == FAILURE)
    {
        resetToDefaults();
    }

    return status;

}

void NVSection::resetToDefaults()
{
    memcpy(_data, _defaultData, _dataSize);
    _dataChanged = true;
    //LogDebug("Reset to factory defaults\r\n");
}

void NVSection::initToDefaults()
{
    memcpy(_data, _defaultData, _dataSize);
    //does not set _dataChanged
}


uint32_t NVSection::calculateBlockAddress(uint8_t blockIndex) const
{
    uint16_t blockSize;
    uint16_t bytesRemaining;
    uint16_t totalSize;
    uint16_t address;

    /*
     * This code finds out how many blocks are used (each block is a flash page of 256 bytes) and
     * sets the address to the absolute address in flash.
     * This is done by finding out how big the block size is, then finding out how many
     * blocks are occupired by this data, then finding the address in flash
     */
    blockSize = _dataSize + static_cast<uint16_t>(DATA_OFFSET);
    bytesRemaining = _minEraseSize - (blockSize & ( _minEraseSize - 1));
    totalSize = bytesRemaining + blockSize;
    address = _nvBaseAddress + (blockIndex * totalSize);

    return address;
}

uint8_t NVSection::verifyBlock(uint32_t address)
{
    uint8_t blockInfo[DATA_OFFSET];
    uint8_t tag;
    uint16_t storedCS;
    uint16_t calcCS;

    _serialFlash->readData(address, blockInfo, static_cast<unsigned int>(DATA_OFFSET));
    tag = blockInfo[TAG_OFFSET];
    _serialFlash->readData(address + static_cast<uint16_t>(DATA_OFFSET), static_cast<uint8_t*>(_data), _dataSize);
    storedCS = blockInfo[CHECKSUM_LSB_OFFSET] | (blockInfo[CHECKSUM_MSB_OFFSET] << 8);

    FletcherChk::ChecksumType checksumA;
    FletcherChk::ChecksumType checksumB;
    FletcherChk::initialize<FletcherChk::Zero>(&checksumA, &checksumB);

    FletcherChk::calculate<FletcherChk::Zero>(blockInfo[TAG_OFFSET],          &checksumA, &checksumB);
    FletcherChk::calculate<FletcherChk::Zero>(blockInfo[DATASIZE_LSB_OFFSET], &checksumA, &checksumB);
    FletcherChk::calculate<FletcherChk::Zero>(blockInfo[DATASIZE_MSB_OFFSET], &checksumA, &checksumB);
    FletcherChk::calculate<FletcherChk::Zero>(static_cast<uint8_t*>(_data), _dataSize, &checksumA, &checksumB);

    calcCS = checksumA | (checksumB << 8);
//    sprintf(gNvDataLocalStr, "tag=%d  calc/stored CS:%04X/%04X\r\n", (uint16)tag, calcCS, storedCS);
//    printk(gNvDataLocalStr);
//
    if (calcCS != storedCS)
    {
        tag = 0;
    }
    return tag;
}

uint16_t NVSection::getBlockDataSize(uint32_t address)
{
    uint8_t data[2];
    uint16_t dataSize;
    _serialFlash->readData(address + static_cast<uint16_t>(DATASIZE_LSB_OFFSET), data, 2);
    dataSize = data[0] | (data[1] << 8);
    return dataSize;
}

bool NVSection::getDataChanged() const
{
    return _dataChanged;
}

void NVSection::setDataChanged(bool hasDataChanged)
{
    _dataChanged = hasDataChanged;
}

} /* namespace Memory */
} /* namespace Embedded */
