#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <gtest/gtest.h>

#include <appareo/utility/queue/Queue.h>
namespace Queue = Appareo::Utility::Queue;

#include <appareo/protocol/asip/ASIP.h>
#include <appareo/protocol/asip/MessageInQueueASIP.h>
#include <appareo/protocol/asip/FindMessageInQueue.h>
namespace ASIP = Appareo::Protocol::ASIP;

#include <appareo/abercrombie/messagePassing/J1939Address.h>
namespace J1939Address = Appareo::Abercrombie::MessagePassing::J1939Address;

static const size_t MESSAGE_BUFFER_SIZE = ASIP::MessageBytesNotInLength
                                        + J1939Address::Length::PAYLOAD_LENGTH;
static const size_t QUEUE_SIZE = MESSAGE_BUFFER_SIZE + 1;

TEST(J1939AddressTest, SerializationTest)
{
    static const uint8_t EXPECTED_SOURCE_ADDRESS = 0x50;
    J1939Address::DataStruct inputData(EXPECTED_SOURCE_ADDRESS);

    uint8_t messageBuffer[MESSAGE_BUFFER_SIZE];
    {
        J1939Address::Serializer serializer;
        ASIP::OutgoingMessage message = serializer.getMessage(inputData);

        message.flattenTo(&(messageBuffer[0]));
    }

    EXPECT_EQ(0xC2, messageBuffer[0]); // Sync 1
    EXPECT_EQ(0x53, messageBuffer[1]); // Sync 2
    EXPECT_EQ(0xFF, messageBuffer[2]); // Class
    EXPECT_EQ(0x00, messageBuffer[3]); // ID
    EXPECT_EQ(0x02, messageBuffer[4]); // Length
    EXPECT_EQ(0x01, messageBuffer[5]); // Payload
    EXPECT_EQ(0x50, messageBuffer[6]); // Payload
    EXPECT_EQ(0x69, messageBuffer[7]); // Checksum A
    EXPECT_EQ(0x9F, messageBuffer[8]); // Checksum B

    J1939Address::DataStruct outputData;
    {
        J1939Address::Deserializer deserializer;

        Queue::Object<QUEUE_SIZE> queue;
        queue.memCopyIn(messageBuffer, MESSAGE_BUFFER_SIZE);

        ASIP::MessageInQueueASIP message = ASIP::findASIPMessageInQueue(queue);

        size_t messageLength = ASIP::MessageBytesNotInLength
                               + J1939Address::Length::PAYLOAD_LENGTH;
        ASSERT_EQ(messageLength, message.getSize());

        outputData = deserializer.getStruct(message);
    }

    EXPECT_TRUE(outputData.resumeSourceAddress);
    EXPECT_EQ(EXPECTED_SOURCE_ADDRESS, outputData.sourceAddress);

    EXPECT_EQ(0, memcmp(&inputData,
                        &outputData,
                        sizeof(J1939Address::DataStruct)));
}


TEST(J1939AddressTest, DefaultConstruction)
{
    J1939Address::DataStruct dut;

    EXPECT_FALSE(dut.resumeSourceAddress);
    EXPECT_EQ(0xFE, dut.sourceAddress);
}
