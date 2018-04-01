#ifndef EMBEDDED_MEMORY_NVSECTION_H_
#define EMBEDDED_MEMORY_NVSECTION_H_

#include <stdint.h>
#include "embedded/memory/IMemory.h"

namespace Embedded {
namespace Memory {

class NVSection
{
    public:
        enum NVSectionLayout
        {
            CHECKSUM_LSB_OFFSET ,
            CHECKSUM_MSB_OFFSET ,
            TAG_OFFSET          ,
            DATASIZE_LSB_OFFSET ,
            DATASIZE_MSB_OFFSET ,
            DATA_OFFSET
        };

        enum NVSectionStatus
        {
            IDLE                    ,
            ERASE_FIRST_SUBSECTOR   ,
            PROCESSING              ,
            ERASING                 ,
            SUCCESS                 ,
            FAILURE
        };

        NVSection(uint32_t nvBaseAddress, void * data, const void * defaultData, uint16_t dataSize, uint8_t numBlocks, Memory::IMemory &serialFlash);
        virtual ~NVSection();

        NVSectionStatus save();
        NVSectionStatus load();

        bool getDataChanged() const;
        void setDataChanged(bool hasDataChanged);

        void resetToDefaults();
        void initToDefaults();


    private:
        uint32_t calculateBlockAddress(uint8_t blockIndex) const;
        uint8_t verifyBlock(uint32_t address);
        uint16_t getBlockDataSize(uint32_t address);

        uint32_t            _nvBaseAddress;
        void               *_data;
        const void         *_defaultData;
        uint16_t            _dataSize;
        uint16_t            _numBlocks;
        Memory::IMemory    *_serialFlash;
        const uint32_t      _pageSize;
        const uint32_t      _minEraseSize;
        uint8_t             _currentBlock;
        uint8_t             _tag;
        NVSectionStatus     _writeState;
        uint16_t            _bytesWritten;
        uint32_t            _writeAddress;
        bool                _dataChanged;       //True if data within NVSection has changed (needs to be saved), otherwise false
};

} /* namespace Memory */
} /* namespace Embedded */

#endif /* EMBEDDED_MEMORY_NVSECTION_H_ */
