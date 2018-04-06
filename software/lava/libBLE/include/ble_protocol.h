
#include <stdint.h>

/**
 * This is the BLE protocol handler. Data is sent to the BLE radio via the
 * normal BLE protocol. There are two BLE characteristics, an input and an
 * output characteristics. When data is received by the BLE unit the data
 * is packaged into this protocol and sent across the SPI interface. The
 * protocol is defined below. Unless otherwise specific each data items is 8-bits
 *
 * | Sync1 | Sync2 | Version 4-bits/Msg ID 4-bits | Length | payload .... | CRC |
 * | 0x55  | 0xAA  | 0x01 / MSG ID | ......
 */

enum BLEMsgID
{
    DATA_IN,
    DATA_OUT,
    MAIN_IMG,
    BLE_IMG
};

typedef void callbackFn(uint8_t * buf, uint32_t len);

#define MaxCallbacks        128
#define MaxBufferSize       512
typedef struct
{
    uint8_t buffer[512];
    uint8_t bufHead;
    uint8_t bufTail;
    callbackFn *callbacks[MaxCallbacks];
} BLEProtocol;

/**
 * @brief Initialize the BLE interface
 * @param ble a pointer to a BLE struct
 */
void ble_protocol_init(BLEProtocol * ble);

/**
 * @brief This function takes the data in the buffer and parses it for valid messages
 * @details The push function is called to push data into the buffer. Then this
 * function parses the data in the buffer and looks for commands and data items
 *
 * @param ble a pointer to a BLE struct
 * @return bool true if valid data was detected
 */
int ble_protocol_parse(BLEProtocol * ble);

/**
 * @brief Pushes data to the BLE Protocol buffer
 * @details Copies data into the BLE ring buffer for later parsing
 *
 * @param ble a pointer to a BLE struct
 * @param data a pointer to the the data to push into the buffer
 * @param len the length of the data to push
 * @return bool true if there was room to push the data into the buffer
 */
int ble_protocol_push(BLEProtocol * ble, uint8_t * data, uint32_t len);

/**
 * @brief Clears the internal BLE buffers
 *
 * @param ble a pointer to a BLE struct
 */
void ble_protocol_clear_buf(BLEProtocol * ble);

/**
 * @brief Registers a callback for a message ID
 * @details When a message has been received, the CRC is good, then the
 * callback for the message ID will be called
 *
 * @param ble a pointer to a BLE struct
 * @param msgID 4-bit message ID
 * @param callback a pointer to a callback function
 */
void ble_protocol_registerCallback(BLEProtocol * ble, uint8_t msgID, callbackFn callback);

/**
 * @brief This function takes a payload and wraps it in the BLE protocol
 *
 * @param dst the destination pointer, it must be large enough to hold the full protocol
 * @param dstLen the size of the dst pointer
 * @param payload a pointer to the payload
 * @param payloadLen the size of the payload
 * @return int the number of bytes placed in the dst or a negative value if an error
 */
int ble_protocol_generatePacket(uint8_t * dst, uint32_t dstLen, uint8_t * payload, uint32_t payloadLen);
