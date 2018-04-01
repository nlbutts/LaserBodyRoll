#include <stdint.h>
#include <gmock/gmock.h>

#include <embedded/memory/IMemory.h>
using Embedded::Memory::IMemory;

class Memory_mock : public IMemory
{
public:
    MOCK_METHOD3(readData, bool(uint32_t address, uint8_t * buf, uint32_t len));
    MOCK_METHOD3(writeDataPoll, bool(uint32_t address, uint8_t * buf, uint32_t len));
    MOCK_METHOD1(eraseSubsectorPoll, bool(uint32_t address));
    MOCK_METHOD0(getSize, uint32_t());
    MOCK_METHOD0(getPageSize, uint32_t());
    MOCK_METHOD0(getMinEraseSize, uint32_t());
    MOCK_METHOD0(isBusy, bool());
};

