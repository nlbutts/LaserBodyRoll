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

uint32_t NORFlash::getSize()
{
    return 0;
}

uint16_t NORFlash::getJEDECID(uint8_t * mfgID, uint16_t * id)
{
    uint8_t data[4];
    uint16_t rv = sendCommand(JEDECID, 4, data);
    *mfgID = data[1];
    *id    = (data[2] << 8) | data[3];
    return rv;
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

