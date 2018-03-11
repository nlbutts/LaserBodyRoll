#include <stdint.h>
#include <gtest/gtest.h>
#include <appareo/abercrombie/AbercrombieJ1939Name.h>

TEST(FrontierJ1939NameTest, CreateFrontierJ1939Name)
{
    //                 X
    // 3520612138 ==> 1101 0001 1101 1000 0100 0111 0010 1010
    Appareo::Abercrombie::AbercrombieJ1939Name abercrombieJ1939Name1(0x26, 3520612138);

    EXPECT_EQ(abercrombieJ1939Name1.getDesiredSourceAddress(),   0x26);
    EXPECT_NE(abercrombieJ1939Name1.getIDNum(),                  3520612138);
    EXPECT_EQ(abercrombieJ1939Name1.getManufacturerCode(),       Appareo::J1939::Messages::J1939Name::APPAREO);
    EXPECT_EQ(abercrombieJ1939Name1.getECUInstances(),           0);
    EXPECT_EQ(abercrombieJ1939Name1.getFunctionInstances(),      0);
    EXPECT_EQ(abercrombieJ1939Name1.getFunction(),               131);
    EXPECT_EQ(abercrombieJ1939Name1.getDeviceClass(),            17);
    EXPECT_EQ(abercrombieJ1939Name1.getDeviceClassInstance(),    0);
    EXPECT_EQ(abercrombieJ1939Name1.getIndustryGroup(),          Appareo::J1939::Messages::J1939Name::AG_AND_FORESTRY);
    EXPECT_EQ(abercrombieJ1939Name1.getArbitraryAddressCap(),    true);

    //                 X
    // 2446870314 ==> 1001 0001 1101 1000 0100 0111 0010 1010
    Appareo::Abercrombie::AbercrombieJ1939Name abercrombieJ1939Name2(0x25, 2446870314);

    EXPECT_EQ(abercrombieJ1939Name2.getDesiredSourceAddress(),   0x25);
    EXPECT_NE(abercrombieJ1939Name2.getIDNum(),                  2446870314);
    EXPECT_EQ(abercrombieJ1939Name2.getManufacturerCode(),       Appareo::J1939::Messages::J1939Name::APPAREO);
    EXPECT_EQ(abercrombieJ1939Name2.getECUInstances(),           0);
    EXPECT_EQ(abercrombieJ1939Name2.getFunctionInstances(),      0);
    EXPECT_EQ(abercrombieJ1939Name2.getFunction(),               131);
    EXPECT_EQ(abercrombieJ1939Name2.getDeviceClass(),            17);
    EXPECT_EQ(abercrombieJ1939Name2.getDeviceClassInstance(),    0);
    EXPECT_EQ(abercrombieJ1939Name2.getIndustryGroup(),          Appareo::J1939::Messages::J1939Name::AG_AND_FORESTRY);
    EXPECT_EQ(abercrombieJ1939Name2.getArbitraryAddressCap(),    true);
}

TEST(FrontierJ1939NameTest, TestArbitraryAddressing1)
{
    //                 X
    // 3520612138 ==> 1101 0001 1101 1000 0100 0111 0010 1010
    Appareo::Abercrombie::AbercrombieJ1939Name name(0x40, 3520612138);

    EXPECT_EQ(name.getID().getSourceAddress(),          0x40);
    EXPECT_EQ(name.executeArbitraryAddressAlgorithm(),  true);
    EXPECT_EQ(name.getID().getSourceAddress(),          0x41);
    EXPECT_EQ(name.executeArbitraryAddressAlgorithm(),  true);
    EXPECT_EQ(name.getID().getSourceAddress(),          0x42);
    EXPECT_EQ(name.executeArbitraryAddressAlgorithm(),  true);
}

TEST(FrontierJ1939NameTest, TestArbitraryAddressing2)
{
    //                 X
    // 3520612138 ==> 1101 0001 1101 1000 0100 0111 0010 1010
    Appareo::Abercrombie::AbercrombieJ1939Name name(0x99, 3520612138);

    EXPECT_EQ(name.getID().getSourceAddress(),          0x99);
    EXPECT_EQ(name.executeArbitraryAddressAlgorithm(),  true);
    EXPECT_EQ(name.getID().getSourceAddress(),          0x9A);
    EXPECT_EQ(name.executeArbitraryAddressAlgorithm(),  true);
    EXPECT_EQ(name.getID().getSourceAddress(),          0x9B);
    EXPECT_EQ(name.executeArbitraryAddressAlgorithm(),  true);
    EXPECT_EQ(name.getID().getSourceAddress(),          0x9C);
    EXPECT_EQ(name.executeArbitraryAddressAlgorithm(),  true);
    EXPECT_EQ(name.getID().getSourceAddress(),          0x9D);
    EXPECT_EQ(name.executeArbitraryAddressAlgorithm(),  false);
}
