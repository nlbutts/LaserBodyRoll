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

#include <appareo/abercrombie/messagePassing/FirmwareVersion.h>
namespace AppVersion = Appareo::Abercrombie::MessagePassing::AppVersion;

static const size_t MESSAGE_BUFFER_SIZE = ASIP::MessageBytesNotInLength
                                        + AppVersion::Length::PAYLOAD_LENGTH;
static const size_t QUEUE_SIZE = MESSAGE_BUFFER_SIZE + 1;

static const char TEST_VERSION[] = "V123456789012345678";
static const char TEST_PN[] = "501010-000000R00";
static const char TEST_HGID[] = "8a776edd4b04ee5cb87cad1146a127827b306e6d+";
static const char TEST_DATE[] = "Wed Jul 22 18:20:46 UTC 2015";

TEST(AppVersionTest, SerializationTest)
{

    AppVersion::DataStruct inputData(TEST_VERSION, TEST_PN, TEST_HGID, TEST_DATE);
    EXPECT_STREQ(TEST_VERSION, inputData.version);
    EXPECT_STREQ(TEST_PN, inputData.partNumber);
    EXPECT_STREQ(TEST_HGID, inputData.mercurialId);
    EXPECT_STREQ(TEST_DATE, inputData.buildDate);
    EXPECT_TRUE(inputData.isValid);

    uint8_t messageBuffer[MESSAGE_BUFFER_SIZE];
    {
        AppVersion::Serializer serializer;
        ASIP::OutgoingMessage message = serializer.getMessage(inputData);

        message.flattenTo(&(messageBuffer[0]));
    }

    EXPECT_EQ(0xC2, messageBuffer[0]); // Sync 1
    EXPECT_EQ(0x53, messageBuffer[1]); // Sync 2
    EXPECT_EQ(0xFF, messageBuffer[2]); // Class
    EXPECT_EQ(0x02, messageBuffer[3]); // ID
    EXPECT_EQ(0x72, messageBuffer[4]); // Length

    AppVersion::DataStruct outputData;
    {
        AppVersion::Deserializer deserializer;

        EXPECT_EQ(0xFF, deserializer.getClass());
        EXPECT_EQ(0x02, deserializer.getId());

        Queue::Object<QUEUE_SIZE> queue;
        queue.memCopyIn(messageBuffer, MESSAGE_BUFFER_SIZE);

        ASIP::MessageInQueueASIP message = ASIP::findASIPMessageInQueue(queue);

        size_t messageLength = ASIP::MessageBytesNotInLength
                             + AppVersion::Length::PAYLOAD_LENGTH;
        ASSERT_EQ(messageLength, message.getSize());

        EXPECT_EQ(0xFF, message.getClass());
        EXPECT_EQ(0x02, message.getId());

        outputData = deserializer.getStruct(message);
    }

    EXPECT_EQ(0, memcmp(&inputData,
                        &outputData,
                        sizeof(AppVersion::DataStruct)));
}


TEST(AppVersionTest, ConstructionTest1)
{
    AppVersion::DataStruct dut;

    EXPECT_EQ('\0', dut.version[AppVersion::Length::VERSION_LENGTH - 1]);
    EXPECT_EQ('\0', dut.partNumber[AppVersion::Length::PARTNUMBER_LENGTH - 1]);
    EXPECT_EQ('\0', dut.mercurialId[AppVersion::Length::MERCURIAL_ID_LENGTH - 1]);
    EXPECT_EQ('\0', dut.buildDate[AppVersion::Length::BUILD_DATE_LENGTH - 1]);

    EXPECT_FALSE(dut.isValid);
}


TEST(AppVersionTest, ConstructionTest2)
{
    AppVersion::DataStruct dut(TEST_VERSION, TEST_PN, TEST_HGID, TEST_DATE);

    EXPECT_STREQ(TEST_VERSION, dut.version);
    EXPECT_STREQ(TEST_PN, dut.partNumber);
    EXPECT_STREQ(TEST_HGID, dut.mercurialId);
    EXPECT_STREQ(TEST_DATE, dut.buildDate);

    EXPECT_EQ('\0', dut.version[AppVersion::Length::VERSION_LENGTH - 1]);
    EXPECT_EQ('\0', dut.partNumber[AppVersion::Length::PARTNUMBER_LENGTH - 1]);
    EXPECT_EQ('\0', dut.mercurialId[AppVersion::Length::MERCURIAL_ID_LENGTH - 1]);
    EXPECT_EQ('\0', dut.buildDate[AppVersion::Length::BUILD_DATE_LENGTH - 1]);

    EXPECT_TRUE(dut.isValid);
}
