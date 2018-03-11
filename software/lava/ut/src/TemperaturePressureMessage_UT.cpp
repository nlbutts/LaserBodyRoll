
#include <stdint.h>
#include <gtest/gtest.h>

// Class under test
#include <appareo/abercrombie/messages/TemperaturePressureMessage.h>
using Appareo::Abercrombie::Messages::TemperaturePressureMessage;

TEST(TemperaturePressureMessageTests, ConstructObject1)
{
    TemperaturePressureMessage msg(5, 25.5, 978.4567);

    EXPECT_EQ(msg.getID().getPGN(),         0x00FFAD);
    EXPECT_EQ(msg.getID().getPriority(),    Appareo::J1939::Messages::CanID::J1939_PRIORITY_6);
    EXPECT_EQ(msg.getDataLength(),          8);

    EXPECT_EQ(msg.getData(0),                  5);

    EXPECT_EQ(msg.getData(1),               0xEC);  // This is due to floating point rounding
    EXPECT_EQ(msg.getData(2),               0x74);
    EXPECT_EQ(msg.getData(3),               0xD2);
    EXPECT_EQ(msg.getData(4),               0x03);

    EXPECT_EQ(msg.getData(5),               0x80);
    EXPECT_EQ(msg.getData(6),               0x19);

    EXPECT_EQ(msg.getData(7),               0xFF);
}

TEST(TemperaturePressureMessageTests, MaxValue)
{
    TemperaturePressureMessage msg(63, 85, 1260);

    EXPECT_EQ(msg.getID().getPGN(),         0x00FFAD);
    EXPECT_EQ(msg.getID().getPriority(),    Appareo::J1939::Messages::CanID::J1939_PRIORITY_6);
    EXPECT_EQ(msg.getDataLength(),          8);

    EXPECT_EQ(msg.getData(0),                 63);

    EXPECT_EQ(msg.getData(1),               0x00);
    EXPECT_EQ(msg.getData(2),               0x00);
    EXPECT_EQ(msg.getData(3),               0xEC);
    EXPECT_EQ(msg.getData(4),               0x04);

    EXPECT_EQ(msg.getData(5),               0x00);
    EXPECT_EQ(msg.getData(6),               0x55);

    EXPECT_EQ(msg.getData(7),               0xFF);
}

TEST(TemperaturePressureMessageTests, MinValue)
{
    TemperaturePressureMessage msg(0, -40, 260);

    EXPECT_EQ(msg.getID().getPGN(),         0x00FFAD);
    EXPECT_EQ(msg.getID().getPriority(),    Appareo::J1939::Messages::CanID::J1939_PRIORITY_6);
    EXPECT_EQ(msg.getDataLength(),          8);

    EXPECT_EQ(msg.getData(0),               0x00);

    EXPECT_EQ(msg.getData(1),               0x00);
    EXPECT_EQ(msg.getData(2),               0x00);
    EXPECT_EQ(msg.getData(3),               0x04);
    EXPECT_EQ(msg.getData(4),               0x01);

    EXPECT_EQ(msg.getData(5),               0x00);
    EXPECT_EQ(msg.getData(6),               0xD8);

    EXPECT_EQ(msg.getData(7),               0xFF);
}

TEST(TemperaturePressureMessageTests, NotAvailable)
{
    TemperaturePressureMessage msg(5, -100, 0);

    EXPECT_EQ(msg.getID().getPGN(),         0x00FFAD);
    EXPECT_EQ(msg.getID().getPriority(),    Appareo::J1939::Messages::CanID::J1939_PRIORITY_6);
    EXPECT_EQ(msg.getDataLength(),          8);

    EXPECT_EQ(msg.getData(0),                  5);

    EXPECT_EQ(msg.getData(1),               0xFF);  // This is due to floating point rounding
    EXPECT_EQ(msg.getData(2),               0xFF);
    EXPECT_EQ(msg.getData(3),               0xFF);
    EXPECT_EQ(msg.getData(4),               0xFF);

    EXPECT_EQ(msg.getData(5),               0xFF);
    EXPECT_EQ(msg.getData(6),               0xFF);

    EXPECT_EQ(msg.getData(7),               0xFF);
}

