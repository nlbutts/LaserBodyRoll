#include <array>

#include "embedded/memory/winbond/defines.h"
#include "embedded/memory/winbond/NORFlash.h"
#include "embedded/micro/interface/ISPI.h"
#include "embedded/device/ChipSelect.h"

using Embedded::Device::ChipSelect;

namespace Embedded {
namespace Memory {
namespace Winbond {


NORFlash::NORFlash(Embedded::Micro::Interface::ISPI &spi,
                   Embedded::Micro::Interface::IGPIO &cs,
                   Embedded::Micro::Interface::ITimer &timer)

: _spi(&spi)
, _cs(&cs)
, _timer(&timer)
{

}

NORFlash::~NORFlash()
{
    _spi = nullptr;
    _cs  = nullptr;
}

bool NORFlash::writeEnable()
{
    return sendCommand(WRITEENABLE);
}

bool NORFlash::volatileSRWriteEnable()
{
    return sendCommand(WRITESTATEN);
}

bool NORFlash::getJEDECID(uint8_t * mfgID, uint16_t * id)
{
    uint8_t txData[4];
    uint8_t rxData[4];

    txData[0] = JEDECID;

    ChipSelect<true> c(*_cs, *_timer, 0, 10);
    uint16_t rv = _spi->write(txData, rxData, 4);
    if (rv == 4)
    {
        *mfgID  = rxData[1];
        *id     = (rxData[2] << 8) | rxData[3];
    }
    else
    {
        *mfgID = 0;
        *id = 0;
    }
    return rv == 4 ? true : false;
}

bool NORFlash::readData(uint32_t address, uint8_t * buf, uint32_t len)
{
    uint8_t commandBuf[4];
    setCommandAndAddress(READDATA, address, commandBuf);
    ChipSelect<true> c(*_cs, *_timer, 0, 10);
    uint16_t rv = _spi->write(commandBuf, sizeof(commandBuf));
    _spi->read(buf, len);
    return rv == 4 ? true : false;
}

bool NORFlash::pageProgram(uint32_t address, uint8_t * buf, uint32_t len)
{
    uint8_t commandBuf[4];
    setCommandAndAddress(PAGEPROG, address, commandBuf);
    ChipSelect<true> c(*_cs, *_timer, 0, 10);
    uint16_t rv = _spi->write(commandBuf, sizeof(commandBuf));
    rv = _spi->write(buf, len);
    return rv == len ? true : false;
}

bool NORFlash::sectorErase(uint32_t address)
{
    return erase(SECTORERASE, address);
}

bool NORFlash::partialBlockErase(uint32_t address)
{
    return erase(BLOCK32ERASE, address);
}

bool NORFlash::BlockErase(uint32_t address)
{
    return erase(BLOCK64ERASE, address);
}

bool NORFlash::chipErase()
{
    return sendCommand(CHIPERASE);
}

uint8_t NORFlash::readStatusReg(SR sr)
{
    constexpr int TransferSize = 2;
    uint8_t txData[TransferSize];
    uint8_t rxData[TransferSize];

    switch (sr)
    {
        case SR1:
            txData[0] = READSTAT1;
            break;
        case SR2:
            txData[0] = READSTAT2;
            break;
        case SR3:
            txData[0] = READSTAT3;
            break;
    }

    ChipSelect<true> c(*_cs, *_timer, 0, 10);
    (void)_spi->write(txData, rxData, TransferSize);
    return rxData[1];
}

bool NORFlash::writeStatusReg(SR sr, uint8_t value)
{
    constexpr int TransferSize = 2;
    uint8_t txData[TransferSize];

    switch (sr)
    {
        case SR1:
            txData[0] = READSTAT1;
            break;
        case SR2:
            txData[0] = READSTAT2;
            break;
        case SR3:
            txData[0] = READSTAT3;
            break;
    }

    txData[1] = value;

    ChipSelect<true> c(*_cs, *_timer, 0, 10);
    (void)_spi->write(txData, TransferSize);
    return true;
}

bool NORFlash::powerDown()
{
    return sendCommand(POWERDOWN);
}

bool NORFlash::reset()
{
    return false;
}

uint32_t NORFlash::getSize()
{
    uint8_t mfgID;
    uint16_t id;
    getJEDECID(&mfgID, &id);
    return id >> 8;
}

bool NORFlash::isBusy()
{
    uint8_t statusReg = readStatusReg(SR1);
    return statusReg & BUSY ? true : false;
}

bool NORFlash::writeDataPoll(uint32_t address, uint8_t * buf, uint32_t len)
{
    writeEnable();
    return pageProgram(address, buf, len);
}

bool NORFlash::eraseSubsectorPoll(uint32_t address)
{
    writeEnable();
    return sectorErase(address);
}

bool NORFlash::sendCommand(uint8_t command)
{
    ChipSelect<true> c(*_cs, *_timer, 0, 10);
    uint16_t rv = _spi->write(&command, 1);
    return rv == 1 ? true : false;
}

void NORFlash::setCommandAndAddress(uint8_t command, uint32_t address, uint8_t * buf)
{
    buf[0] = command;
    buf[1] = static_cast<uint8_t>(address >> 16);
    buf[2] = static_cast<uint8_t>(address >> 8);
    buf[3] = static_cast<uint8_t>(address);
}

bool NORFlash::erase(uint8_t command, uint32_t address)
{
    uint8_t commandBuf[4];
    setCommandAndAddress(command, address, commandBuf);
    ChipSelect<true> c(*_cs, *_timer, 0, 10);
    uint16_t rv = _spi->write(commandBuf, sizeof(commandBuf));
    return rv == sizeof(commandBuf) ? true : false;
}



} // namespace Winbond
} // namespace Memory
} // namespace Interface

