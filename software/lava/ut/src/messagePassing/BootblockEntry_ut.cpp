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

#include <appareo/abercrombie/messagePassing/BootblockEntry.h>
namespace BootblockEntry = Appareo::Abercrombie::MessagePassing::BootblockEntry;

static const size_t MESSAGE_BUFFER_SIZE =   ASIP::MessageBytesNotInLength
                                     + BootblockEntry::Length::PAYLOAD_LENGTH;
static const size_t QUEUE_SIZE = MESSAGE_BUFFER_SIZE + 1;

TEST(BootblockEntryDataTest, SerializationTest)
{
    static const BootblockEntry::Reason EXPECTED_ENTRY_REASON = BootblockEntry::RECEIVE_FIRMWARE_UPDATE;
    BootblockEntry::DataStruct inputData(EXPECTED_ENTRY_REASON);

    uint8_t messageBuffer[MESSAGE_BUFFER_SIZE];
    {
        BootblockEntry::Serializer serializer;
        ASIP::OutgoingMessage message = serializer.getMessage(inputData);

        message.flattenTo(&(messageBuffer[0]));
    }

    EXPECT_EQ(0xC2, messageBuffer[0]); // Sync 1
    EXPECT_EQ(0x53, messageBuffer[1]); // Sync 2
    EXPECT_EQ(0xFF, messageBuffer[2]); // Class
    EXPECT_EQ(0x01, messageBuffer[3]); // ID
    EXPECT_EQ(0x01, messageBuffer[4]); // Length
    EXPECT_EQ(0x01, messageBuffer[5]); // Payload
    EXPECT_EQ(0x19, messageBuffer[6]); // Checksum A
    EXPECT_EQ(0x37, messageBuffer[7]); // Checksum B

    BootblockEntry::DataStruct outputData;
    {
        BootblockEntry::Deserializer deserializer;

        EXPECT_EQ(0xFF, deserializer.getClass());
        EXPECT_EQ(0x01, deserializer.getId());

        Queue::Object<QUEUE_SIZE> queue;
        queue.memCopyIn(messageBuffer, MESSAGE_BUFFER_SIZE);

        ASIP::MessageInQueueASIP message = ASIP::findASIPMessageInQueue(queue);

        size_t messageLength = ASIP::MessageBytesNotInLength
                               + BootblockEntry::Length::PAYLOAD_LENGTH;
        ASSERT_EQ(messageLength, message.getSize());

        EXPECT_EQ(0xFF, message.getClass());
        EXPECT_EQ(0x01, message.getId());

        outputData = deserializer.getStruct(message);
    }

    EXPECT_EQ(EXPECTED_ENTRY_REASON, outputData.entryReason);
    EXPECT_EQ(0, memcmp(&inputData,
                        &outputData,
                        sizeof(BootblockEntry::DataStruct)));
}


TEST(BootblockEntryDataTest, EnumConstants)
{
    EXPECT_EQ(0, BootblockEntry::UNKNOWN);
    EXPECT_EQ(1, BootblockEntry::RECEIVE_FIRMWARE_UPDATE);
    EXPECT_EQ(2, BootblockEntry::EXTRACT_FIRMWARE_UPDATE);
}

