#include <stdint.h>

#ifndef EMBEDDED_MICRO_INTERFACE_I_FLASH_H
#define EMBEDDED_MICRO_INTERFACE_I_FLASH_H

namespace Embedded {
namespace Micro {
namespace Interface {

/**
 * @brief Interface class for program flash drivers
 */
class IFlash
{
public:
    /**
     * @brief Destructor
     */
    virtual ~IFlash() {}

    /**
     * @brief Gets the sector number for a given address
     *
     * @param address Address to use
     * @return Sector number of address, or -1 on failure
     */
    virtual int8_t findSector(uint32_t address) const = 0;

    /**
     * @brief Gets the size of a given sector
     *
     * @param sector Sector number.
     * @return Sector size, in bytes. If the sector number is out of
     *         range, then 0 will be returned
     */
    virtual uint32_t getSectorSize(int8_t sector) const = 0;

    /**
     * @brief Erase an entire sector
     *
     * @param sector Sector to erase
     * @return true on success, else false
     */
    virtual bool eraseSector(int8_t sector) = 0;


    /**
     * @brief Write an entire block of data to flash
     *
     * @param buffer Buffer of data to write
     * @param length Length, in bytes, of the buffer
     * @param address Address to start writing at
     *
     * @return true on success, else false
     */
    virtual bool programData(const uint8_t* buffer, uint32_t length, uint32_t address) = 0;


    /**
     * @brief Unlock the flash for writing.
     *
     * @details This must be called before calling the erase or program
     *          functions.
     */
    virtual void unlockFlash(void) = 0;

    /**
     * @brief Lock the flash (set to read-only)
     * @details This should be called after programming in finished.
     */
    virtual void lockFlash(void) = 0;

protected:
    /**
     * @brief Constructor
     */
    IFlash() {}
};

} // namespace Interface
} // namespace Micro
} // namespace Embedded

#endif /* EMBEDDED_MICRO_INTERFACE_I_FLASH_H */
