// /**
//  * Copyright (c) 2011 Appareo Systems, LLC.
//  * 1810 NDSU Research Park Circle North
//  * Fargo ND, 58102
//  * All rights reserved.
//  *
//  * This is the confidential and proprietary information of Appareo Systems, LLC. You shall not
//  * disclose such confidential information and shall use it only in accordance with the terms
//  * of the license agreement you entered into with Appareo.
//  *
//  *
//  * Copyright Version 1.0
//  */

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <appareo/shadow/eeprom/Eeprom.h>
#include <appareo/shadow/eeprom/ShadowRAM.h>

namespace UT {

namespace Eeprom = Appareo::Shadow::EEPROM::Eeprom;
namespace ShadowRAM = Appareo::Shadow::EEPROM::ShadowRAM;
namespace Redundant = ShadowRAM::Section::Redundant;
using Eeprom::Data;
using Eeprom::Address;
using ShadowRAM::Bank;
using ShadowRAM::Size;
using ShadowRAM::Crc;

using ::testing::Return;

class MockEeprom : public Eeprom::Base
{
public:
    MockEeprom() {}

    MOCK_METHOD2(WriteData, void(Eeprom::Address, Eeprom::Data));
    MOCK_METHOD0(WriteDataComplete, bool());

    MOCK_METHOD1(ReadData, void(Eeprom::Address));
    MOCK_METHOD1(ReadDataBlocking, uint8_t(Eeprom::Address));
    MOCK_METHOD1(ReadDataComplete, bool(Eeprom::Data &));
};

class TestEeprom : public Eeprom::Base
{
public:
    typedef Eeprom::Data    Data;
    typedef Eeprom::Address Address;
    TestEeprom()
    {
        for (int x = 0; x < 1000; ++x)
        {
            _data[x] = 0xFF;
        }
        _writeComplete = true;
    }

    Data _data[1000];
    Address _address;
    bool _writeComplete;

    void WriteData(Address address, Data data)  {   _data[address] = data;  }
    bool WriteDataComplete()                    {   return _writeComplete;  }

    void ReadData(Address address)              {   _address = address;     }
    uint8_t ReadDataBlocking(Address address)        {   return _data[address]; }
    bool ReadDataComplete(Data & data)          {   data = _data[_address];
                                                    return true;            }
};

class ShadowRAMTest_ManagerMockEeprom : public ::testing::Test
{
public:
    struct testData
    {
        int i;
        float f;
    } data, defaults;

    MockEeprom mockEeprom;
    ShadowRAM::Manager::Base manager;
    Eeprom::Address bank1;
    Eeprom::Address bank2;
    ShadowRAM::Section::Redundant::Object<testData> redundant;

    ShadowRAMTest_ManagerMockEeprom() :
        mockEeprom(),
        manager(mockEeprom),
        bank1(0),
        bank2(100),
        redundant(manager, data, defaults, bank1, bank2)
    {
        data.i = 7;
        data.f = 3.41;

        defaults.i = 19;
        defaults.f = 20.0;
    }

public:
    inline Data*        get_redundant__data() { return redundant._data; }
    inline Address      get_redundant__bankAddresses(Bank bank) { return redundant._bankAddresses[bank]; }
    inline Size         get_redundant__size() { return redundant._size; }
    inline const Data*  get_redundant__defaults() { return redundant._defaults; }
    inline ShadowRAM::Section::InitializationState 
                        get_redundant__initState() { return redundant._initState; }
    inline Eeprom::Base* get_redundant__eeprom() { return redundant._eeprom; }

    inline bool call_redundant_CrcBank(Crc expectedCrc)
                        { return redundant.doesCalculatedBankCrcMatch(expectedCrc); }

    inline Eeprom::Base* get_manager__eeprom() { return manager._eeprom; }
    inline ShadowRAM::Section::Base* get_manager__head() { return manager._head; }

    inline ShadowRAM::Section::Base* get_section_base__next(ShadowRAM::Section::Base& base)
                        { return base._next; }
};

class ShadowRAMTest_ManagerTestEeprom : public ::testing::Test
{
public:
    struct testData
    {
        int i;
        float f;
    } data, defaults;

    TestEeprom testEeprom;
    ShadowRAM::Manager::Base manager;
    Eeprom::Address bank1;
    Eeprom::Address bank2;
    ShadowRAM::Section::Redundant::Object<testData> redundant;

    ShadowRAMTest_ManagerTestEeprom() :
        testEeprom(),
        manager(testEeprom),
        bank1(0),
        bank2(100),
        redundant(manager, data, defaults, bank1, bank2)
    {}

    void SetupGoodData()
    {
        data.i = 7;
        data.f = 3.41;

        SetupDefaults();

        int i = 7;
        float f = 3.41;
        int fi = *reinterpret_cast<int *>(&f);

        testEeprom._data[ 0] = testEeprom._data[100] = 0x04;
        testEeprom._data[ 1] = testEeprom._data[101] = 0x93;
        testEeprom._data[ 2] = testEeprom._data[102] = 0x5F;
        testEeprom._data[ 3] = testEeprom._data[103] = 0xA6;

        testEeprom._data[ 4] = testEeprom._data[104] = 8;
        testEeprom._data[ 5] = testEeprom._data[105] = (i >>  0) & 0xFF;
        testEeprom._data[ 6] = testEeprom._data[106] = (i >>  8) & 0xFF;
        testEeprom._data[ 7] = testEeprom._data[107] = (i >> 16) & 0xFF;
        testEeprom._data[ 8] = testEeprom._data[108] = (i >> 24) & 0xFF;
        testEeprom._data[ 9] = testEeprom._data[109] = (fi >>  0) & 0xFF;
        testEeprom._data[10] = testEeprom._data[110] = (fi >>  8) & 0xFF;
        testEeprom._data[11] = testEeprom._data[111] = (fi >> 16) & 0xFF;
        testEeprom._data[12] = testEeprom._data[112] = (fi >> 24) & 0xFF;
    }

    void SetupBlankFlash()
    {
        data.i = 7;
        data.f = 3.41;

        SetupDefaults();

        testEeprom._data[ 0] = testEeprom._data[100] = 0xFF;
        testEeprom._data[ 1] = testEeprom._data[101] = 0xFF;
        testEeprom._data[ 2] = testEeprom._data[102] = 0xFF;
        testEeprom._data[ 3] = testEeprom._data[103] = 0xFF;

        testEeprom._data[ 4] = testEeprom._data[104] = 0xFF;
        testEeprom._data[ 5] = testEeprom._data[105] = 0xFF;
        testEeprom._data[ 6] = testEeprom._data[106] = 0xFF;
        testEeprom._data[ 7] = testEeprom._data[107] = 0xFF;
        testEeprom._data[ 8] = testEeprom._data[108] = 0xFF;
        testEeprom._data[ 9] = testEeprom._data[109] = 0xFF;
        testEeprom._data[10] = testEeprom._data[110] = 0xFF;
        testEeprom._data[11] = testEeprom._data[111] = 0xFF;
        testEeprom._data[12] = testEeprom._data[112] = 0xFF;
    }

    void SetupEmptyEeprom()
    {
        data.i = 7;
        data.f = 3.41;

        SetupDefaults();

        testEeprom._data[ 0] = testEeprom._data[100] = 0x00;
        testEeprom._data[ 1] = testEeprom._data[101] = 0x00;
        testEeprom._data[ 2] = testEeprom._data[102] = 0x00;
        testEeprom._data[ 3] = testEeprom._data[103] = 0x00;

        testEeprom._data[ 4] = testEeprom._data[104] = 0x00;
        testEeprom._data[ 5] = testEeprom._data[105] = 0x00;
        testEeprom._data[ 6] = testEeprom._data[106] = 0x00;
        testEeprom._data[ 7] = testEeprom._data[107] = 0x00;
        testEeprom._data[ 8] = testEeprom._data[108] = 0x00;
        testEeprom._data[ 9] = testEeprom._data[109] = 0x00;
        testEeprom._data[10] = testEeprom._data[110] = 0x00;
        testEeprom._data[11] = testEeprom._data[111] = 0x00;
        testEeprom._data[12] = testEeprom._data[112] = 0x00;
    }

    void SetupDefaults()
    {
        defaults.i = 19;
        defaults.f = 20.0;
    }

public:
    inline ShadowRAM::Section::InitializationState 
                    get_redundant__initState() { return redundant._initState; }
    inline Redundant::REDUNDANT_STATE
                    get_redundant__state() { return redundant._state; }
    inline void     set_redundant__state(Redundant::REDUNDANT_STATE state) 
                        { redundant._state = state; }
    inline Data     get_redundant__syncBank() { return redundant._syncBank; }
    inline uint8_t  get_redundant__bankScanCounter() { return redundant._bankScanCounter; }
    inline const Data get_redundant_DataStart() { return Redundant::Layout::DataStartIndex; }
    inline const Data get_redundant_Crc1Index() { return Redundant::Layout::Crc1Index; }
};



// // Test ShadowRAM::Manager::Base constructor, RegisterSection
TEST_F(ShadowRAMTest_ManagerMockEeprom, Access) 
{
    EXPECT_EQ(&mockEeprom,  get_manager__eeprom());
    EXPECT_EQ(&redundant,   get_manager__head());

    ShadowRAM::Section::Redundant::Object<testData> redundant2(manager, data, defaults, bank1, bank2);

    EXPECT_EQ(&redundant2,  get_manager__head());
    EXPECT_EQ(&redundant ,  get_section_base__next(redundant2));

}

// Test ShadowRAM::Section::Redundant::Base constructor
TEST_F(ShadowRAMTest_ManagerMockEeprom, Access2) {
    EXPECT_EQ((void *)&data,                    (void *)get_redundant__data());
    EXPECT_EQ((void *)&defaults,                (void *)get_redundant__defaults());
    EXPECT_EQ(sizeof(data),                             get_redundant__size());
    EXPECT_EQ(bank1,                                    get_redundant__bankAddresses(0));
    EXPECT_EQ(bank2,                                    get_redundant__bankAddresses(1));
    EXPECT_EQ(ShadowRAM::Section::Uninitialized,        get_redundant__initState());
    EXPECT_EQ(&mockEeprom,                              get_redundant__eeprom());
}



TEST_F(ShadowRAMTest_ManagerMockEeprom, LoadDefaults)
{
    redundant.LoadDefaults();

    EXPECT_EQ(data.i, defaults.i);
    EXPECT_EQ(data.f, defaults.f);
}

TEST_F(ShadowRAMTest_ManagerMockEeprom, CrcBank)
{
    EXPECT_EQ(true, call_redundant_CrcBank(0xA65F9304));
}

TEST_F(ShadowRAMTest_ManagerTestEeprom, InitializeRegisteredSectionsBothPass)
{
    SetupGoodData();
    manager.InitializeRegisteredSections();
    EXPECT_EQ(ShadowRAM::Section::SuccessfullyRestoredAllBanksPassed, get_redundant__initState());
}

TEST_F(ShadowRAMTest_ManagerTestEeprom, InitializeRegisteredSectionsBlankFlash)
{
    SetupBlankFlash();
    manager.InitializeRegisteredSections();
    EXPECT_EQ(ShadowRAM::Section::ChecksumsFailed, get_redundant__initState());

    EXPECT_EQ(data.i, defaults.i);
    EXPECT_EQ(data.f, defaults.f);
}


TEST_F(ShadowRAMTest_ManagerTestEeprom, InitializeRegisteredSectionsEmptyEeprom)
{
    SetupEmptyEeprom();
    manager.InitializeRegisteredSections();
    EXPECT_EQ(ShadowRAM::Section::ChecksumsFailed, get_redundant__initState());

    EXPECT_EQ(data.i, defaults.i);
    EXPECT_EQ(data.f, defaults.f);
}


TEST_F(ShadowRAMTest_ManagerTestEeprom, InitializeRegisteredSectionsOnePass)
{
    SetupGoodData();
    testEeprom._data[  5] = 1;
    manager.InitializeRegisteredSections();
    EXPECT_EQ(ShadowRAM::Section::SuccessfullyRestoredNotAllBanksPassed, get_redundant__initState());
}

TEST_F(ShadowRAMTest_ManagerTestEeprom, InitializeRegisteredSectionsOtherPass)
{
    SetupGoodData();
    testEeprom._data[105] = 1;
    manager.InitializeRegisteredSections();
    EXPECT_EQ(ShadowRAM::Section::SuccessfullyRestoredNotAllBanksPassed, get_redundant__initState());
}

TEST_F(ShadowRAMTest_ManagerTestEeprom, InitializeRegisteredSectionsFail)
{
    SetupGoodData();
    testEeprom._data[  5] = 1;
    testEeprom._data[105] = 1;
    manager.InitializeRegisteredSections();
    EXPECT_EQ(ShadowRAM::Section::ChecksumsFailed,      get_redundant__initState());
}

TEST_F(ShadowRAMTest_ManagerTestEeprom, SyncData)
{
    SetupDefaults();
    manager.InitializeRegisteredSections();
    EXPECT_EQ(ShadowRAM::Section::ChecksumsFailed,      get_redundant__initState());

    testEeprom._writeComplete = false;
    manager.Update();
    testEeprom._writeComplete = true;
    for (int i = 0; i < 100; ++i)
    {
        manager.Update();
    }

    manager.InitializeRegisteredSections();
    EXPECT_EQ(ShadowRAM::Section::SuccessfullyRestoredAllBanksPassed,      get_redundant__initState());
}

TEST_F(ShadowRAMTest_ManagerTestEeprom, SyncDataBankUpdateExceeded)
{
    SetupDefaults();
    manager.InitializeRegisteredSections();
    EXPECT_EQ(ShadowRAM::Section::ChecksumsFailed,      get_redundant__initState());

    while (get_redundant__state() == ShadowRAM::Section::Redundant::SCAN)
    {
        manager.Update();
    }
    while (get_redundant__state() != ShadowRAM::Section::Redundant::SCAN)
    {
        manager.Update();
    }
    EXPECT_EQ(get_redundant__bankScanCounter(), 1);
    EXPECT_EQ(get_redundant__syncBank(), 0);
    data.i++;

    while (get_redundant__state() == ShadowRAM::Section::Redundant::SCAN)
    {
        manager.Update();
    }
    while (get_redundant__state() != ShadowRAM::Section::Redundant::SCAN)
    {
        manager.Update();
    }
    EXPECT_EQ(get_redundant__bankScanCounter(), 2);
    EXPECT_EQ(get_redundant__syncBank(), 0);
    data.i++;

    while (get_redundant__state() == ShadowRAM::Section::Redundant::SCAN)
    {
        manager.Update();
    }
    EXPECT_EQ(get_redundant__bankScanCounter(), 3);
    while (get_redundant__state() != ShadowRAM::Section::Redundant::SCAN)
    {
        manager.Update();
    }
    EXPECT_EQ(get_redundant__bankScanCounter(), 0);
    EXPECT_EQ(get_redundant__syncBank(), 1);
}

TEST_F(ShadowRAMTest_ManagerTestEeprom, SyncDataFailBankTwo)
{
    SetupDefaults();
    manager.InitializeRegisteredSections();
    EXPECT_EQ(ShadowRAM::Section::ChecksumsFailed,      get_redundant__initState());

    while(get_redundant__syncBank() == 0)
    {
        manager.Update();
    }

    /* Sync 4 bytes on the second bank */
    manager.Update();
    manager.Update();
    manager.Update();
    manager.Update();

    /* Bank 2 should fail */
    manager.InitializeRegisteredSections();
    EXPECT_EQ(ShadowRAM::Section::SuccessfullyRestoredNotAllBanksPassed,      get_redundant__initState());
}

TEST_F(ShadowRAMTest_ManagerTestEeprom, SyncDataFailBankOne)
{
    SetupDefaults();
    manager.InitializeRegisteredSections();
    EXPECT_EQ(ShadowRAM::Section::ChecksumsFailed,      get_redundant__initState());

    while(get_redundant__syncBank() == 0)
    {
        manager.Update();
    }

    while(get_redundant__syncBank() == 1)
    {
        manager.Update();
    }

    data.i = 42;

    /* Sync 4 bytes on the second bank */
    manager.Update();

    /* Bank 2 should fail */
    manager.InitializeRegisteredSections();
    EXPECT_EQ(ShadowRAM::Section::SuccessfullyRestoredNotAllBanksPassed,      get_redundant__initState());
}

TEST_F(ShadowRAMTest_ManagerTestEeprom, TestMaxWriteAttempts)
{
    SetupDefaults();
    manager.InitializeRegisteredSections();
    EXPECT_EQ(ShadowRAM::Section::ChecksumsFailed,      get_redundant__initState());

    manager.Update();
    testEeprom._data[get_redundant_DataStart()] = 0xFF;
    manager.Update();
    testEeprom._data[get_redundant_DataStart()] = 0xFF;
    manager.Update();
    testEeprom._data[get_redundant_DataStart()] = 0xFF;
    manager.Update();
    testEeprom._data[get_redundant_DataStart()] = 0xFF;
    manager.Update();

    EXPECT_EQ(get_redundant__syncBank(), 1);

    while (get_redundant__state() != ShadowRAM::Section::Redundant::WRITE_CRC_BYTE_1)
    {
        manager.Update();
    }

    testEeprom._data[100 + get_redundant_Crc1Index()] = 0;
    manager.Update();
    testEeprom._data[100 + get_redundant_Crc1Index()] = 0;
    manager.Update();
    testEeprom._data[100 + get_redundant_Crc1Index()] = 0;
    manager.Update();
    testEeprom._data[100 + get_redundant_Crc1Index()] = 0;
    manager.Update();

    EXPECT_EQ(get_redundant__syncBank(), 0);
}

TEST_F(ShadowRAMTest_ManagerTestEeprom, TestInvalidState)
{
    SetupDefaults();
    manager.InitializeRegisteredSections();
    EXPECT_EQ(ShadowRAM::Section::ChecksumsFailed,      get_redundant__initState());

    manager.Update();    
    EXPECT_EQ(get_redundant__state(), ShadowRAM::Section::Redundant::SCAN);

    /* Set to an invalid state */
    set_redundant__state(static_cast<ShadowRAM::Section::Redundant::REDUNDANT_STATE>(1234));
    EXPECT_EQ(get_redundant__state(), 1234);

    manager.Update();
    EXPECT_EQ(get_redundant__state(), ShadowRAM::Section::Redundant::SCAN);
}

} // namespace UT

