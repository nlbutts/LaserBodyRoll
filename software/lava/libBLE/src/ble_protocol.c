#include <stdlib.h>
#include <string.h>
#include "ble_protocol.h"
#include "checksum.h"


//************************************************************* DEFINES AND ENUM

#define SYNC1               0x55
#define SYNC2               0xAA
#define PROTOCOL_OVERHEAD   5
#define PRTOCOL_VERSION     0

const UUID_CONFIG UUIDInfo[] =
{
    {PUUID_ANALOG1_SLOPE,       4},
    {PUUID_ANALOG1_OFFSET,      4},
    {PUUID_ANALOG2_SLOPE,       4},
    {PUUID_ANALOG2_OFFSET,      4},
    {PUUID_OPEN_DRAIN_PULL_UP,  1},
    {PUUID_LASER_DISTANCE,      4},
    {PUUID_ACCELX,              2},
    {PUUID_ACCELY,              2},
    {PUUID_ACCELZ,              2},
    {PUUID_GYROX,               2},
    {PUUID_GYROY,               2},
    {PUUID_GYROZ,               2},
    {PUUID_AUTO_LEVEL_GAIN,     4},
    {PUUID_EPOCH,               4},
    {PUUID_SUPER_CAP_VOLTAGE,   2},
};


//************************************************************* STATIC FUNCTIONS

/**
 * @brief Push a byte into the circular buffer
 *
 * @param ble pointer to the BLE struct
 * @param data the byte to push
 *
 * @return postive values if successul, negative if not
 */
static inline int ble_protocol_push(BLEProtocol * ble, uint8_t data);
/**
 * @brief Pops the top byte off of the circular buffer
 *
 * @param ble pointer to the BLE struct
 * @param data pointer to a byte to pop
 *
 * @return postive values if successul, negative if not
 */
static inline int ble_protocol_pop(BLEProtocol * ble, uint8_t * data);
/**
 * @brief Peak in the buffer
 *
 * @param ble pointer to the BLE struct
 * @param data pointer to a byte to peek
 * @param offset the offset into the buffer to peak
 *
 * @return postive values if successul, negative if not
 */
static inline int ble_protocol_peek(BLEProtocol * ble, uint8_t * data, int offset);
/**
 * @brief Indicates how many bytes are in the circular buffer
 *
 * @param ble pointer to the BLE struct
 *
 * @return int bytes in buffer
 */
static inline int ble_protocol_bytes_in_buffer(BLEProtocol * ble);
/**
 * @brief Advances the tail by some amount
 *
 * @param ble pointer to the BLE struct
 * @param amount the amount to increase the tail pointer
 *
 * @return postive values if successul, negative if not
 */
static inline int ble_protocol_advance_tail(BLEProtocol * ble, int amount);
/**
 * @brief Calls the callback if it is not null
 *
 * @param ble pointer to the BLE struct
 * @param msgID the message ID to callback
 * @param but pointer to a buffer
 * @param len of the buffer
 *
 * @return postive values if successul, negative if not
 */
static void ble_protocol_callCallback(BLEProtocol * ble, uint8_t msgID, uint8_t * buf, int len);

//*************************************************************** MAIN FUNCTIONS
void ble_protocol_init(BLEProtocol * ble)
{
    ble->head = 0;
    ble->tail  = 0;
    for (uint8_t i = 0; i < MaxCallbacks; i++)
    {
        ble->callbacks[i] = NULL;
    }
}

int ble_protocol_parse(BLEProtocol * ble)
{
    uint8_t version;
    uint8_t msgID;
    uint8_t msgBuffer[MaxBufferSize];

    if (ble_protocol_bytes_in_buffer(ble) > PROTOCOL_OVERHEAD)
    {
        ble_protocol_peek(ble, &msgBuffer[PROTOCOL_SYNC1], PROTOCOL_SYNC1);
        ble_protocol_peek(ble, &msgBuffer[PROTOCOL_SYNC2], PROTOCOL_SYNC2);
        if ((msgBuffer[PROTOCOL_SYNC1] == SYNC1) && (msgBuffer[PROTOCOL_SYNC2] == SYNC2))
        {
            // pop version/MSG ID
            ble_protocol_peek(ble, &msgBuffer[PROTOCOL_VERID], PROTOCOL_VERID);
            version = (msgBuffer[PROTOCOL_VERID] >> 4) & 0x0F;
            msgID   = (msgBuffer[PROTOCOL_VERID]     ) & 0x0F;
            if (version != PRTOCOL_VERSION)
            {
                return -1;
            }
            ble_protocol_peek(ble, &msgBuffer[PROTOCOL_LEN], PROTOCOL_LEN);
            if (ble_protocol_bytes_in_buffer(ble) >= (msgBuffer[PROTOCOL_LEN] + PROTOCOL_OVERHEAD))
            {
                for (int i = 0; i < msgBuffer[PROTOCOL_LEN]; i++)
                {
                    ble_protocol_peek(ble, &msgBuffer[PROTOCOL_PAYLOAD + i], i + PROTOCOL_PAYLOAD);
                }
                uint8_t rxCrc;
                ble_protocol_peek(ble, &rxCrc, msgBuffer[PROTOCOL_LEN] + PROTOCOL_PAYLOAD);
                uint8_t calcCrc = crc_8(msgBuffer, msgBuffer[PROTOCOL_LEN] + PROTOCOL_PAYLOAD);
                if (rxCrc == calcCrc)
                {
                    // CRCs are good
                    ble_protocol_callCallback(ble, msgID, &msgBuffer[PROTOCOL_PAYLOAD], msgBuffer[PROTOCOL_LEN]);
                }
                ble_protocol_advance_tail(ble,  msgBuffer[PROTOCOL_LEN] + PROTOCOL_OVERHEAD);
            }
            // Exit and wait for more bytes to be inserted into this buffer
        }
        else
        {
            // The first byte in the buffer is not the sync byte, pop the top
            uint8_t data;
            ble_protocol_pop(ble, &data);
        }
    }

    return ble_protocol_bytes_in_buffer(ble);
}

void ble_protocol_clear_buf(BLEProtocol * ble)
{
    ble->head = 0;
    ble->tail = 0;
}

void ble_protocol_registerCallback(BLEProtocol * ble, uint8_t msgID, callbackFn callback)
{
    if (msgID < MaxCallbacks)
    {
        ble->callbacks[msgID] = callback;
    }
}

int ble_protocol_generatePacket(uint8_t * dst, uint32_t dstLen, uint8_t version, uint8_t msgID, uint8_t * payload, uint32_t payloadLen)
{
    int bytesReturned = 0;
    if (dstLen > (payloadLen + PROTOCOL_PAYLOAD + 1))
    {
        dst[PROTOCOL_SYNC1] = SYNC1;
        dst[PROTOCOL_SYNC2] = SYNC2;
        dst[PROTOCOL_VERID] = (version << 4) | msgID;
        dst[PROTOCOL_LEN]   = payloadLen;
        memcpy(&dst[PROTOCOL_PAYLOAD], payload, payloadLen);
        dst[payloadLen + PROTOCOL_PAYLOAD] = crc_8(dst, payloadLen + PROTOCOL_PAYLOAD);
        bytesReturned = PROTOCOL_PAYLOAD + payloadLen + 1;
    }
    return bytesReturned;
}

int ble_protocol_push_msg(BLEProtocol * ble, uint8_t * data, uint32_t len)
{
    int success;
    for (uint32_t i = 0; i < len; i++)
    {
        success = ble_protocol_push(ble, data[i]);
        if (success == 0)
            return 0;
    }
    return 1;
}


static inline int ble_protocol_push(BLEProtocol * ble, uint8_t data)
{
    int success = 0;
    if (((ble->head - ble->tail) & (MaxBufferSize - 1)) < (MaxBufferSize - 1))
    {
        ble->buffer[ble->head++] = data;
        ble->head &= (MaxBufferSize - 1);
        success = 1;
    }
    return success;
}

static inline int ble_protocol_pop(BLEProtocol * ble, uint8_t * data)
{
    int success = 0;
    if (ble->head != ble->tail)
    {
        *data = ble->buffer[ble->tail++];
        ble->tail &= MaxBufferSize - 1;
        success = 1;
    }
    return success;
}

static inline int ble_protocol_peek(BLEProtocol * ble, uint8_t * data, int offset)
{
    int success = 0;
    int tempTail = (ble->tail + offset) & (MaxBufferSize - 1);
    if (ble->head > tempTail)
    {
        *data = ble->buffer[tempTail];
        success = 1;
    }
    return success;
}

static inline int ble_protocol_bytes_in_buffer(BLEProtocol * ble)
{
    return (ble->head - ble->tail) & (MaxBufferSize - 1);
}

static inline int ble_protocol_advance_tail(BLEProtocol * ble, int amount)
{
    int success = 0;
    if (ble_protocol_bytes_in_buffer(ble) >= amount)
    {
        ble->tail += amount;
        ble->tail &= MaxBufferSize - 1;
        success = 1;
    }
    return success;
}

static void ble_protocol_callCallback(BLEProtocol * ble, uint8_t msgID, uint8_t * buf, int len)
{
    if (ble->callbacks[msgID] != NULL)
    {
        ble->callbacks[msgID](buf, len);
    }
}
