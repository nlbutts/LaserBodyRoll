#ifndef IMEMORY_FS_H_
#define IMEMORY_FS_H_

#include <stdint.h>
#include <string>
#include <fstream>
#include <vector>

#include <embedded/memory/IMemory.h>
using Embedded::Memory::IMemory;

namespace Embedded {
namespace Memory {

using std::string;
using std::ofstream;


/**
 * @brief This is an interface class for a memory device
**/
class Memory_FS : public IMemory
{
public:
    Memory_FS(int MaxSize)
    : _dataSize(MaxSize)
    , _data(nullptr)
    , busyFlag(false)
    {
        _data = new uint8_t[_dataSize];
    };
    ~Memory_FS()
    {
        std::ofstream ofs("nv_data.bin", std::ios::binary);
        ofs.write((char*)_data, _dataSize);
        ofs.close();

        delete [] _data;
        _data = nullptr;
    };
    bool readData(uint32_t address, uint8_t * buf, uint32_t len)
    {
        if ((address + len) <= _dataSize)
        {
            memcpy(buf, &_data[address], len);
            return true;
        }
        return false;
    }
    bool writeDataPoll(uint32_t address, uint8_t * buf, uint32_t len)
    {
        if ((address + len) <= _dataSize)
        {
            memcpy(&_data[address], buf, len);
            return true;
        }
        return false;
    }
    bool eraseSubsectorPoll(uint32_t address)
    {
        (void)address;
        return true;
    }
    uint32_t getSize()
    {
        return 64;
    }
    uint32_t getPageSize()
    {
        return 256;
    }
    uint32_t getMinEraseSize()
    {
        return 4096;
    }
    bool isBusy()
    {
        return busyFlag;
    }

    const uint32_t          _dataSize;
    uint8_t                *_data;
    bool                    busyFlag;
};


} // namespace Memory
} // namespace Embedded


#endif // IMEMORY_FS_H_
