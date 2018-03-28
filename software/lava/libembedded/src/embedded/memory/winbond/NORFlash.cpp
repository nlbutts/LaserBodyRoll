#include <array>

#include "embedded/memory/winbond/defines.h"
#include "embedded/memory/winbond/NORFlash.h"
#include "embedded/micro/interface/ISPI.h"
#include "embedded/device/ChipSelect.h"

using Embedded::Device::ChipSelect;

namespace Embedded {
namespace Memory {
namespace Winbond {


NORFlash::NORFlash(Embedded::Micro::Interface::ISPI &spi,
                   Embedded::Micro::Interface::IGPIO &cs,
                   Embedded::Micro::Interface::ITimer &timer)

: _spi(&spi)
, _cs(&cs)
, _timer(&timer)
{

}

NORFlash::~NORFlash()
{
    _spi = nullptr;
    _cs  = nullptr;
}

bool NORFlash::writeEnable()
{
    bool success = sendCommand(WRITEENABLE, 0, nullptr);
}


uint32_t NORFlash::getSize()
{
    bool success = false;
    uint8_t data[4];
    uint16_t bytesRxed = sendCommand(JEDECID, 4, data);
    if (bytesRxed == 4)
}

bool NORFlash::getJEDECID(uint8_t * mfgID, uint16_t * id)
{
    bool success = false;
    uint8_t data[4];
    uint16_t bytesRxed = sendCommand(JEDECID, 4, data);
    if (bytesRxed == 4)
    {
        *mfgID  = data[1];
        *id     = (data[2] << 8) | data[3];
        success = true;
    }
    else
    {
        *mfgID = 0;
        *id = 0;
    }
    return success;
}

uint16_t NORFlash::sendCommand(uint8_t command, uint32_t expectedBytes, uint8_t * buf)
{
    uint8_t commandBuf[7];
    commandBuf[0] = command;
    ChipSelect<true> c(*_cs, *_timer, 0, 10);
    uint16_t rv = _spi->write(commandBuf, buf, expectedBytes);
    return rv;
}


} // namespace Winbond
} // namespace Memory
} // namespace Interface

