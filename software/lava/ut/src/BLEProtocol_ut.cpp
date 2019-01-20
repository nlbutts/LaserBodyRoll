#include <stdint.h>
#include <cstdlib>
#include <gtest/gtest.h>

extern "C" {
#include "ble_protocol.h"
}

int _callbackMsg[200] = {0};
int _dataInCallbackCnt   = 0;
int _dataOutCallbackCnt  = 0;
int _mainImgCallbackCnt  = 0;
int _bleImgCallbackCnt   = 0;

TEST(BLEProtocolTest, CreatePacket)
{
    constexpr int bufSize = 1000;
    uint8_t outBuffer[bufSize];
    uint8_t payload[bufSize];
    memset(outBuffer, 0, bufSize);

    for (int i = 0; i < 1000; i++)
    {
        payload[i] = i;
    }

    int rv = ble_protocol_generatePacket(outBuffer, bufSize, 0, DATA_IN, payload, 5);

    EXPECT_EQ(rv, 10);
    EXPECT_EQ(outBuffer[0], 0x55);          // sync1
    EXPECT_EQ(outBuffer[1], 0xAA);          // sync2
    EXPECT_EQ(outBuffer[2], 0x00 | 0x00);   // version/id
    EXPECT_EQ(outBuffer[3], 5);             // payload length
    EXPECT_EQ(outBuffer[4], payload[0]);    // data 1
    EXPECT_EQ(outBuffer[5], payload[1]);    // data 2
    EXPECT_EQ(outBuffer[6], payload[2]);    // data 3
    EXPECT_EQ(outBuffer[7], payload[3]);    // data 4
    EXPECT_EQ(outBuffer[8], payload[4]);    // data 5
    EXPECT_EQ(outBuffer[9], 0x25);           // checksum
}

void dataInCallback(uint8_t * buf, uint32_t len)
{
    _dataInCallbackCnt++;
    memcpy(_callbackMsg, buf, len);
}

void dataOutCallback(uint8_t * buf, uint32_t len)
{
    _dataOutCallbackCnt++;
    memcpy(_callbackMsg, buf, len);
}

void mainImgCallback(uint8_t * buf, uint32_t len)
{
    _mainImgCallbackCnt++;
    memcpy(_callbackMsg, buf, len);
}

void bleImgCallback(uint8_t * buf, uint32_t len)
{
    _bleImgCallbackCnt++;
    memcpy(_callbackMsg, buf, len);
}

int testMessagePushAndCallback(BLEProtocol *ble, uint8_t msgID, uint8_t payloadBytes)
{
    constexpr int bufSize = 200;
    uint8_t outBuffer[bufSize];
    uint8_t payload[bufSize];
    memset(outBuffer, 0, bufSize);

    uint8_t value = 0;
    int bytesInBuffer;

    for (uint8_t index = 0; index < payloadBytes; index++)
    {
        payload[index] = value++;
    }

    int rv = 0;
    int success = 0;

    // Test all of the callbacks
    rv = ble_protocol_generatePacket(outBuffer, bufSize, 0, msgID, payload, value);
    success = ble_protocol_push_msg(ble, outBuffer, rv);
    EXPECT_EQ(success, 1);
    bytesInBuffer = ble_protocol_parse(ble);
    success = memcmp(payload, _callbackMsg, value);
    EXPECT_EQ(success, 0);
    return bytesInBuffer;
}

TEST(BLEProtocolTest, TestPacketRx)
{
    BLEProtocol ble;
    ble_protocol_init(&ble);
    ble_protocol_registerCallback(&ble, DATA_IN,     dataInCallback);
    ble_protocol_registerCallback(&ble, DATA_OUT,    dataOutCallback);
    ble_protocol_registerCallback(&ble, MAIN_IMG,    mainImgCallback);
    ble_protocol_registerCallback(&ble, BLE_IMG,     bleImgCallback);

    EXPECT_EQ(_dataInCallbackCnt, 0);
    EXPECT_EQ(testMessagePushAndCallback(&ble, DATA_IN, 43), 0);
    EXPECT_EQ(_dataInCallbackCnt, 1);

    EXPECT_EQ(_dataOutCallbackCnt, 0);
    EXPECT_EQ(testMessagePushAndCallback(&ble, DATA_OUT, 43), 0);
    EXPECT_EQ(_dataOutCallbackCnt, 1);

    EXPECT_EQ(_mainImgCallbackCnt, 0);
    EXPECT_EQ(testMessagePushAndCallback(&ble, MAIN_IMG, 128), 0);
    EXPECT_EQ(_mainImgCallbackCnt, 1);

    EXPECT_EQ(_bleImgCallbackCnt, 0);
    EXPECT_EQ(testMessagePushAndCallback(&ble, BLE_IMG, 128), 0);
    EXPECT_EQ(_bleImgCallbackCnt, 1);
}

TEST(BLEProtocolTest, MultipleMessagesInBuffer)
{
    BLEProtocol ble;
    ble_protocol_init(&ble);
    ble_protocol_registerCallback(&ble, DATA_IN,     dataInCallback);
    ble_protocol_registerCallback(&ble, DATA_OUT,    dataOutCallback);
    ble_protocol_registerCallback(&ble, MAIN_IMG,    mainImgCallback);
    ble_protocol_registerCallback(&ble, BLE_IMG,     bleImgCallback);

    constexpr int bufSize = 200;
    uint8_t payload[bufSize];
    uint8_t outBuffer[bufSize];
    memset(outBuffer, 0, bufSize);

    uint8_t value = 0;
    int bytesInBuffer;

    for (uint8_t index = 0; index < bufSize/2; index++)
    {
        payload[index] = value++;
    }

    int rv = 0;
    int success = 0;

    // Test all of the callbacks
    rv = ble_protocol_generatePacket(outBuffer, bufSize, 0, MAIN_IMG, payload, value);
    success = ble_protocol_push_msg(&ble, outBuffer, rv);
    EXPECT_EQ(success, 1);
    success = ble_protocol_push_msg(&ble, outBuffer, rv);
    EXPECT_EQ(success, 1);
    success = ble_protocol_push_msg(&ble, outBuffer, rv);
    EXPECT_EQ(success, 1);
    success = ble_protocol_push_msg(&ble, outBuffer, rv);
    EXPECT_EQ(success, 1);

    bytesInBuffer = ble_protocol_parse(&ble);
    success = memcmp(payload, _callbackMsg, value);
    EXPECT_EQ(success, 0);
    EXPECT_EQ(bytesInBuffer, 315);

    bytesInBuffer = ble_protocol_parse(&ble);
    success = memcmp(payload, _callbackMsg, value);
    EXPECT_EQ(success, 0);
    EXPECT_EQ(bytesInBuffer, 210);

    bytesInBuffer = ble_protocol_parse(&ble);
    success = memcmp(payload, _callbackMsg, value);
    EXPECT_EQ(success, 0);
    EXPECT_EQ(bytesInBuffer, 105);

    bytesInBuffer = ble_protocol_parse(&ble);
    success = memcmp(payload, _callbackMsg, value);
    EXPECT_EQ(success, 0);
    EXPECT_EQ(bytesInBuffer, 0);
}

TEST(BLEProtocolTest, BadCRC)
{
    BLEProtocol ble;
    ble_protocol_init(&ble);
    ble_protocol_registerCallback(&ble, DATA_IN,     dataInCallback);
    ble_protocol_registerCallback(&ble, DATA_OUT,    dataOutCallback);
    ble_protocol_registerCallback(&ble, MAIN_IMG,    mainImgCallback);
    ble_protocol_registerCallback(&ble, BLE_IMG,     bleImgCallback);

    constexpr int bufSize = 200;
    uint8_t payload[bufSize];
    uint8_t outBuffer[bufSize];
    memset(outBuffer, 0, bufSize);

    uint8_t value = 0;

    for (uint8_t index = 0; index < 5; index++)
    {
        payload[index] = value++;
    }

    int rv = 0;
    int success = 0;

    _dataInCallbackCnt = 0;

    // Test a bad CRC
    rv = ble_protocol_generatePacket(outBuffer, bufSize, 0, DATA_IN, payload, value);
    outBuffer[value + PROTOCOL_PAYLOAD]++;
    success = ble_protocol_push_msg(&ble, outBuffer, rv);
    EXPECT_EQ(success, 1);
    EXPECT_EQ(_dataInCallbackCnt, 0);
    success = ble_protocol_parse(&ble);
    EXPECT_EQ(success, 0);
    EXPECT_EQ(_dataInCallbackCnt, 0);
}

TEST(BLEProtocolTest, OverflowBuffer)
{
    BLEProtocol ble;
    ble_protocol_init(&ble);
    ble_protocol_registerCallback(&ble, DATA_IN,     dataInCallback);
    ble_protocol_registerCallback(&ble, DATA_OUT,    dataOutCallback);
    ble_protocol_registerCallback(&ble, MAIN_IMG,    mainImgCallback);
    ble_protocol_registerCallback(&ble, BLE_IMG,     bleImgCallback);

    constexpr int bufSize = 200;
    uint8_t payload[bufSize];
    uint8_t outBuffer[bufSize];
    memset(outBuffer, 0, bufSize);

    uint8_t value = 0;
    uint8_t rv = 0;
    uint8_t success = 0;

    for (uint8_t index = 0; index < bufSize / 2; index++)
    {
        payload[index] = value++;
    }

    // Test pushing until the buffer fills up
    rv = ble_protocol_generatePacket(outBuffer, bufSize, 0, BLE_IMG, payload, bufSize / 2);
    success = ble_protocol_push_msg(&ble, outBuffer, rv);
    EXPECT_EQ(success, 1);
    success = ble_protocol_push_msg(&ble, outBuffer, rv);
    EXPECT_EQ(success, 1);
    success = ble_protocol_push_msg(&ble, outBuffer, rv);
    EXPECT_EQ(success, 1);
    success = ble_protocol_push_msg(&ble, outBuffer, rv);
    EXPECT_EQ(success, 1);
    success = ble_protocol_push_msg(&ble, outBuffer, rv);
    EXPECT_EQ(success, 0);
    success = ble_protocol_push_msg(&ble, outBuffer, rv);
    EXPECT_EQ(success, 0);

    ble_protocol_clear_buf(&ble);
    success = ble_protocol_push_msg(&ble, outBuffer, rv);
    EXPECT_EQ(success, 1);

}
