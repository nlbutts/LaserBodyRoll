#include "project.h"
#include "protocol.h"


/**
* Constants
*/
#define SYNC1   0x55
#define SYNC2   0xAA

#define MAX_PACKET_SIZE     6

/**
* Local variables
*/
static uint8_t piData[MAX_PACKET_SIZE];
static uint8_t piDataIndex = 0;
static uint8_t checksum = 0;

static uint8_t psocData[MAX_PACKET_SIZE];
static uint8_t psocDataIndex = 0;

static uint16_t outputVoltage;
static uint8_t piBits;

/**
* Local Functions
*/
static uint8_t calculateChecksum(uint8_t * buf, uint8_t length);

enum ProtocolPos
{
    SYNC1_POS,
    SYNC2_POS,
    VOLTAGE_MSB_POS,
    VOLTAGE_LSB_POS,
    COMMAND_BITS_POS,
    CHECKSUM_POS,
};

typedef enum
{
    SYNC1_STATE,
    SYNC2_STATE,
    DATA
} ProtocolState;

static ProtocolState state;

void protocol_init()
{
    state = SYNC1_STATE;
}

void protocol_pushPacket()
{
    if (SPI_SpiUartGetTxBufferSize() == 0)
    {
        GREEN_Write(0);
        psocData[0] = SYNC1;
        psocData[1] = SYNC2;
        psocData[2] = 0;
        psocData[3] = 0;
        psocData[4] = (DIGITAL_IN2_Read() << 1) | DIGITAL_IN1_Read();
        psocData[5] = calculateChecksum(psocData, MAX_PACKET_SIZE - 1);
        SPI_SpiUartPutArray(psocData, MAX_PACKET_SIZE);
    }
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
                    state = DATA;
                    piData[piDataIndex++] = temp;
                }
                else
                {
                    state = SYNC1_STATE;
                }

                break;
            case DATA:
                if (piDataIndex < (MAX_PACKET_SIZE - 1))
                {
                    piData[piDataIndex++] = temp;
                }
                else
                {
                    if (calculateChecksum(piData, MAX_PACKET_SIZE - 1) == piData[CHECKSUM_POS])
                    {
                        // Checksums match
                        outputVoltage = ((uint16_t)piData[0] << 8);
                        outputVoltage |= piData[1];
                        piBits = piData[2];
                    }
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
