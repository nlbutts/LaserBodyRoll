#include <stdint.h>
#include <gtest/gtest.h>

#include <appareo/j1939/messages/CanMessage.h>
using Appareo::J1939::Messages::CanMessage;
#include <appareo/j1939/messages/CanID.h>
using Appareo::J1939::Messages::CanID;

#include <appareo/abercrombie/messages/RebootCommandParser.h>
using Appareo::Abercrombie::Messages::RebootCommandParser;

static const uint32_t PGN           = 0x00EF00;
static const uint32_t INVALID_PGN   = 0x00EE00;

TEST(RebootCommandParserTest, InvalidPGN)
{
    RebootCommandParser dut(PGN);

    CanMessage message;
    message.setDataLength(8);
    message.setID(CanID(Appareo::J1939::Messages::CanID::J1939_PRIORITY_6, INVALID_PGN, 0));
    message.setData(static_cast<uint8_t>(0x06),0);
    message.setData(static_cast<uint8_t>(0x00),1);
    message.setData(static_cast<uint8_t>(0x00),2);
    message.setData(static_cast<uint8_t>(0x00),3);
    message.setData(static_cast<uint8_t>(0x00),4);
    message.setData(static_cast<uint8_t>(0x00),5);
    message.setData(static_cast<uint8_t>(0x00),6);
    message.setData(static_cast<uint8_t>(0x00),7);

    EXPECT_FALSE(dut.isCommandValid(message));
}


TEST(RebootCommandParserTest, InvalidDLC)
{
    RebootCommandParser dut(PGN);

    CanMessage message;
    message.setDataLength(7);   // Invalid
    message.setID(CanID(Appareo::J1939::Messages::CanID::J1939_PRIORITY_6, PGN, 0));
    message.setData(static_cast<uint8_t>(0x06),0);
    message.setData(static_cast<uint8_t>(0x00),1);
    message.setData(static_cast<uint8_t>(0x00),2);
    message.setData(static_cast<uint8_t>(0x00),3);
    message.setData(static_cast<uint8_t>(0x00),4);
    message.setData(static_cast<uint8_t>(0x00),5);
    message.setData(static_cast<uint8_t>(0x00),6);
    message.setData(static_cast<uint8_t>(0x00),7);

    EXPECT_FALSE(dut.isCommandValid(message));
}

TEST(RebootCommandParserTest, InvalidCommandID)
{
    RebootCommandParser dut(PGN);

    CanMessage message;
    message.setDataLength(8);
    message.setID(CanID(Appareo::J1939::Messages::CanID::J1939_PRIORITY_6, PGN, 0));
    message.setData(static_cast<uint8_t>(0x05),0); // Invalid
    message.setData(static_cast<uint8_t>(0x00),1);
    message.setData(static_cast<uint8_t>(0x00),2);
    message.setData(static_cast<uint8_t>(0x00),3);
    message.setData(static_cast<uint8_t>(0x00),4);
    message.setData(static_cast<uint8_t>(0x00),5);
    message.setData(static_cast<uint8_t>(0x00),6);
    message.setData(static_cast<uint8_t>(0x00),7);

    EXPECT_FALSE(dut.isCommandValid(message));
}


TEST(RebootCommandParserTest, ValidCommand)
{
    RebootCommandParser dut(PGN);

    CanMessage message;
    message.setDataLength(8);
    message.setID(CanID(Appareo::J1939::Messages::CanID::J1939_PRIORITY_6, PGN, 0));
    message.setData(static_cast<uint8_t>(0x06),0);
    message.setData(static_cast<uint8_t>(0x00),1);
    message.setData(static_cast<uint8_t>(0x00),2);
    message.setData(static_cast<uint8_t>(0x00),3);
    message.setData(static_cast<uint8_t>(0x00),4);
    message.setData(static_cast<uint8_t>(0x00),5);
    message.setData(static_cast<uint8_t>(0x00),6);
    message.setData(static_cast<uint8_t>(0x00),7);

    EXPECT_TRUE(dut.isCommandValid(message));
}
