#ifndef EMBEDDED_MICRO_INTERFACE_ISPI_H_
#define EMBEDDED_MICRO_INTERFACE_ISPI_H_

#include <stdint.h>

namespace Embedded {
namespace Micro {
namespace Interface {

class ISPI
{
public:
    /**
     * Destructor
     */
    virtual ~ISPI() {}

    /**
     * This function is used to read data from the SPI interface. This function will
     * send out a 0 for every byte that is read in. This is a blocking function.
     *
     * @param ptr Pointer to the receive character buffer.
     *            Must be at least len bytes long
     * @param len Number of bytes to read into the rx buffer.
     */
    virtual void read(uint8_t * rx, uint16_t len) = 0;

    /**
     * Writes data to the SPI port, this function blocks until the data is transmitted.
     *
     * @param tx Pointer to the transmit data buffer. Must not be NULL.
     * @param len Length of the data to transmit
     * @return Number of bytes transmitted or 0 if a transfer failed
     */
    virtual uint16_t write(const uint8_t * tx, uint16_t len) = 0;

    /**
     * Writes data to the SPI port, this function blocks until the data is transmitted.
     *
     * @param tx Pointer to the transmit data buffer. Must not be NULL. The buffer must
     *           be at least len bytes long.
     * @param rx Pointer to the receive data buffer. Must be NULL, or at least
     *           len bytes long.
     * @param len Length of the data to transmit
     * @return Number of bytes transmitted or 0 if a transfer failed
     */
    virtual uint16_t write(const uint8_t * tx, uint8_t * rx, uint16_t len) = 0;

protected:
    /**
     * Constructor
     */
    ISPI() {}
};

} // namespace Interface
} // namespace Micro
} // namespace Embedded

#endif /* EMBEDDED_MICRO_INTERFACE_ISPI_H_ */