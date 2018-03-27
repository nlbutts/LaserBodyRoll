#ifndef EMBEDDED_MEMORY_WINBOND_NORFLASH
#define EMBEDDED_MEMORY_WINBOND_NORFLASH

#include <stdint.h>

namespace Embedded {
namespace Micro {
namespace Interface {
class ISPI;
class IGPIO;
class ITimer;
}
}

namespace Memory {
namespace Winbond {

/**
 * @brief This is a generic class for Winbond Serial NOR flash memories
 * @details This class handles reading and writing data to/from the flash
 * The current implementation is a polled based version.
 *
 * @param spi A reference to the SPI interface class
 * @param cs A reference to the chip select device
 *
 * @return [description]
 */
class NORFlash
{
public:
    NORFlash(Embedded::Micro::Interface::ISPI &spi,
             Embedded::Micro::Interface::IGPIO &cs,
             Embedded::Micro::Interface::ITimer &timer);
    ~NORFlash();

    uint32_t getSize();
    uint16_t getJEDECID(uint8_t * mfgID, uint16_t * id);

private:
    uint16_t sendCommand(uint8_t command, uint32_t expectedBytes, uint8_t * buf);


private:
    Embedded::Micro::Interface::ISPI    *_spi;
    Embedded::Micro::Interface::IGPIO   *_cs;
    Embedded::Micro::Interface::ITimer  *_timer;
};


} // namespace Winbond
} // namespace Memory
} // namespace Embedded


#endif // EMBEDDED_MEMORY_WINBOND_NORFLASH
