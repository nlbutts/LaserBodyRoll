#include <stdint.h>

// COMMANDS
enum ProtocolMessages
{
    Invalid,
    IncomingData,
    OutgoingData,
    Reprogram
};

/**
* This function processes and sends data to to the Pi
*
* @param protocolCommand which command to send
*/
void protocol_pushPacket(uint8_t protocolCommand);
/**
* This function checks and process packets from the Pi
*/
void protocol_process();

