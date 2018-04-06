#include <stdint.h>
#include <cstdlib>
#include <gtest/gtest.h>

extern "C" {
#include "ble_protocol.h"
}

TEST(BLEProtocolTest, CreatePacket)
{
    constexpr int bufSize = 1000;
    uint8_t outBuffer[bufSize];
    uint8_t payload[bufSize];

    for (int i = 0; i < 1000; i++)
    {
        payload[i] = std::rand();
    }

    int rv = ble_protocol_generatePacket(outBuffer, bufSize, payload, 5);

    EXPECT_EQ(rv, 25);
    EXPECT_EQ(outBuffer[0], 0x55);          // sync1
    EXPECT_EQ(outBuffer[1], 0xAA);          // sync2
    EXPECT_EQ(outBuffer[2], 0x10 | 0x00);   // version/id
    EXPECT_EQ(outBuffer[3], 5);             // payload length
    EXPECT_EQ(outBuffer[4], payload[0]);    // data 1
    EXPECT_EQ(outBuffer[5], payload[1]);    // data 2
    EXPECT_EQ(outBuffer[6], payload[2]);    // data 3
    EXPECT_EQ(outBuffer[7], payload[3]);    // data 4
    EXPECT_EQ(outBuffer[8], payload[4]);    // data 5
    EXPECT_EQ(outBuffer[9], 0x0);           // checksum
}

TEST(BLEProtocolTest, TestPacketRx)
{
    BLEProtocol ble;
    ble_protocol_init(&ble);

    EXPECT_TRUE(true);
}
