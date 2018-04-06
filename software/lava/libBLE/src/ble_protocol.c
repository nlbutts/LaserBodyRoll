#include <stdlib.h>
#include "ble_protocol.h"

void ble_protocol_init(BLEProtocol * ble)
{
    ble->bufHead = 0;
    ble->bufTail  = 0;
    for (uint8_t i = 0; i < MaxCallbacks; i++)
    {
        ble->callbacks[i] = NULL;
    }
}

int ble_protocol_parse(BLEProtocol * ble)
{
    return 0;
}

int ble_protocol_push(BLEProtocol * ble, uint8_t * data, uint32_t len)
{
    return 0;
}

void ble_protocol_clear_buf(BLEProtocol * ble)
{

}

void ble_protocol_registerCallback(BLEProtocol * ble, uint8_t msgID, callbackFn callback)
{

}

int ble_protocol_generatePacket(uint8_t * dst, uint32_t dstLen, uint8_t * payload, uint32_t payloadLen)
{
    return -1;
}
