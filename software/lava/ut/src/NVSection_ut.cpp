#include <stdint.h>
#include <gtest/gtest.h>

#include "embedded/memory/NVSection.h"
using Embedded::Memory::NVSection;

#include "embedded/memory/Memory_fs.h"
using Embedded::Memory::Memory_FS;

#include <iostream>
using std::cout;
using std::endl;

// Define the test structure
struct TestData
{
    uint32_t a;
    uint32_t b;
    uint8_t  c;
    float    d;
};

// Define constants

constexpr TestData  DefaultData = {1,2,3,4.0f};
constexpr uint32_t  NumOfSections = 3;
constexpr uint32_t  MemsizeInBytes = 64/8 * 1024 * 1024;

class NVSectionTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        memset(&_data, 0, sizeof(TestData));
        _mem = new Memory_FS(MemsizeInBytes);
    }

    TestData    _data;
    Memory_FS  *_mem;
};

TEST_F(NVSectionTest, Construction)
{
    //NVSection sec(0, static_cast<void*>(&_data), static_cast<void*>(&_defaultData), sizeof(TestData), 3, mem);
    NVSection sec(0, &_data, &DefaultData, sizeof(TestData), NumOfSections, *_mem);

    NVSection::NVSectionStatus status = sec.load();
    EXPECT_EQ(status, NVSection::FAILURE);

    _mem->busyFlag = false;
    for (uint32_t i = 0; i < NumOfSections; i++)
    {
        while (sec.save() != NVSection::SUCCESS)
        {
        }
    }
}

TEST_F(NVSectionTest, ValidRead)
{
    //NVSection sec(0, static_cast<void*>(&_data), static_cast<void*>(&_defaultData), sizeof(TestData), 3, mem);
    NVSection sec(0, &_data, &DefaultData, sizeof(TestData), NumOfSections, *_mem);

    NVSection::NVSectionStatus status = sec.load();
    EXPECT_EQ(status, NVSection::FAILURE);

    _mem->busyFlag = false;
    for (uint32_t i = 0; i < NumOfSections; i++)
    {
        while (sec.save() != NVSection::SUCCESS)
        {
        }
    }

    status = sec.load();
    EXPECT_EQ(status, NVSection::SUCCESS);

    // The first block should be the most up-to-date. Correct it and see if it still recovers
    _mem->_data[0] = 0;
    status = sec.load();
    EXPECT_EQ(status, NVSection::SUCCESS);

    // Correct the next block and verify it is still succesfull
    _mem->_data[_mem->getMinEraseSize()] = 0;
    status = sec.load();
    EXPECT_EQ(status, NVSection::SUCCESS);

    // Correct the last block and verify it is fails
    _mem->_data[_mem->getMinEraseSize() * 2] = 0;
    status = sec.load();
    EXPECT_EQ(status, NVSection::FAILURE);
}

