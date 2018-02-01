#include "project.h"
#include "protocol.h"


/**
* Constants
*/
#define SYNC1   0x55
#define SYNC2   0xAA

#define MAX_PACKET_SIZE     16
#define PKT_OVERHEAD        5

/**
* Local variables
*/
static uint8_t piData[MAX_PACKET_SIZE];
static uint8_t piDataIndex = 0;
static uint8_t checksum = 0;

static uint8_t psocData[MAX_PACKET_SIZE];

static uint8_t command = Invalid;
static uint8_t payload_length = 0;

static uint16_t outputVoltage;
static uint8_t piBits;

/**
* Local Functions
*/
/**
* This function calculates the checksum of the packet
*
* @param buf the input buffer
* @param length the length of the buffer
* @return uint8_t the checksum
*/
static uint8_t calculateChecksum(uint8_t * buf, uint8_t length);
/**
* This function executes the command after it has been received and the checksum passes
*
* @param command the incoming command
* @param payload a pointer to the length verified payload
*/
void executeCommand(uint8_t command, uint8_t * payload);
/**
* This resets the received state machine
*/
void reset();
/**
* Starts the reprogramming session
*/
void startReprogramming();


enum ProtocolPos
{
    SYNC1_POS,
    SYNC2_POS,
    CMD_POS,
    LEN_POS,
    DATA_POS
};

typedef enum
{
    SYNC1_STATE,
    SYNC2_STATE,
    CMD_STATE,
    LEN_STATE,
    DATA_STATE
} ProtocolState;

static ProtocolState state;

void protocol_init()
{
    state = SYNC1_STATE;
}

void protocol_pushPacket(uint8_t protocolCommand)
{
    uint8_t packetLength;
    if (SPI_SpiUartGetTxBufferSize() == 0)
    {
        psocData[SYNC1_POS] = SYNC1;
        psocData[SYNC2_POS] = SYNC2;
        switch (protocolCommand)
        {
            case OutgoingData:
                packetLength           = 3 + PKT_OVERHEAD - 1;
                psocData[CMD_POS]      = OutgoingData;
                psocData[LEN_POS]      = 2;
                psocData[DATA_POS]     = 0;
                psocData[DATA_POS + 1] = 0;
                psocData[DATA_POS + 2] = (DIGITAL_IN2_Read() << 1) | DIGITAL_IN1_Read();
                break;
        }
        psocData[5] = calculateChecksum(psocData, packetLength);
        SPI_SpiUartPutArray(psocData, packetLength);
    }
    GREEN_Write(0);
}

void protocol_process()
{
    while (SPI_SpiUartGetRxBufferSize() > 0)
    {
        RED_Write(0);
        uint8_t temp = SPI_SpiUartReadRxData();
        switch (state)
        {
            case SYNC1_STATE:
                if (temp == SYNC1)
                {
                    state = SYNC2_STATE;
                    piData[piDataIndex++] = temp;
                }
                break;
            case SYNC2_STATE:
                if (temp == SYNC2)
                {
                    state = CMD_STATE;
                    piData[piDataIndex++] = temp;
                }
                else
                {
                    state = SYNC1_STATE;
                }

                break;
            case CMD_STATE:
                command = temp;
                piData[piDataIndex++] = temp;
                state = LEN_STATE;
                break;
            case LEN_STATE:
                payload_length = temp;
                piData[piDataIndex++] = temp;
                state = DATA_STATE;
                break;
            case DATA_STATE:
                if (piDataIndex < (payload_length + PKT_OVERHEAD))
                {
                    piData[piDataIndex++] = temp;
                }
                else if (calculateChecksum(piData, payload_length + PKT_OVERHEAD - 1) == piData[payload_length + PKT_OVERHEAD - 1])
                {
                    // Checksums match
                    executeCommand(command, &piData[DATA_POS]);
                    reset();
                }
                break;
        }
    }
}

uint8_t calculateChecksum(uint8_t * buf, uint8_t length)
{
    uint8_t checksum = 0;
    for (uint8_t i = 0; i < length; i++)
    {
        checksum += buf[i];
    }
    return checksum;
}

void executeCommand(uint8_t command, uint8_t * payload)
{
    switch (command)
    {
        case IncomingData:
            outputVoltage = ((uint16_t)payload[0] << 8);
            outputVoltage |= payload[1];
            piBits = payload[2];
            break;
        case OutgoingData:
            break;
        case Reprogram:
            startReprogramming();
            break; 
    }
}

void reset()
{
    piDataIndex = 0;
    checksum = 0;

    command = Invalid;
    payload_length = 0;
    state = SYNC1_STATE;
}

void startReprogramming()
{
    static int foo;
    foo++;
}