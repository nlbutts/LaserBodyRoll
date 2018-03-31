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
    enum SR
    {
        SR1,
        SR2,
        SR3
    };


    /**
     * @brief Constructor for a NOR flash
     * @details The constructor takes an ISPI object, an IGPIO chip select,
     * and an ITimer.
     *
     * @param spi an interface to a SPI device
     * @param cs an interface for a chip select
     * @param timer an interface for a timer
     */
    NORFlash(Embedded::Micro::Interface::ISPI &spi,
             Embedded::Micro::Interface::IGPIO &cs,
             Embedded::Micro::Interface::ITimer &timer);
    /**
     * @brief Destructor
     */
    ~NORFlash();
    /**
     * @brief Enables writes to the part
     * @return bool true if the write to the part was successul
     */
    bool writeEnable();
    /**
     * @brief Writes the volatile SR registers
     * @return bool true if the write to the part was successul
     */
    bool volatileSRWriteEnable();
    /**
     * @brief Disables writes to the part
     * @return bool true if the write to the part was successul
     */
    bool writeDisable();
    /**
     * @brief Returns the JEDEC ID of this part
     *
     * @param mfgID the MFG ID (see datasheets)
     * @param id part ID (see datasheet)
     *
     * @return bool true if the JEDEC ID was read
     */
    bool getJEDECID(uint8_t * mfgID, uint16_t * id);
    /**
     * @brief Reads data from the part
     * @details Reads a bunch of data from the part. Be careful, this could
     * take some time
     *
     * @param address the address to read data
     * @param buf a pointer to the buffer to store the return data
     * @param len the number of bytes to read
     * @param fastRead perform a fast read from the part
     * @return bool true if the read was succesful
     */
    bool read(uint32_t address, uint8_t * buf, uint32_t len, bool fastRead = false);
    /**
     * @brief Writes a page to the part
     * @details Writes a single page to the part
     *
     * @param address the address to write data
     * @param buf a pointer to the buffer to store the return data
     * @param len the number of bytes to read
     * @return bool true if the write was succesful
     */
    bool pageProgram(uint32_t address, uint8_t * buf, uint32_t len);
    /**
     * @brief Erases a 4KB sector
     *
     * @param address the address to erase
     * @return bool true if the erase was succesful
     */
    bool sectorErase(uint32_t address);
    /**
     * @brief Erases a 32KB Block
     *
     * @param address the address to erase
     * @return bool true if the erase was succesful
     */
    bool partialBlockErase(uint32_t address);
    /**
     * @brief Erases a 64KB Block
     *
     * @param address the address to erase
     * @return bool true if the erase was succesful
     */
    bool BlockErase(uint32_t address);
    /**
     * @brief Erases the entire chip, be careful
     *
     * @return bool true if the erase was succesful
     */
    bool chipErase();
    /**
     * @brief Reads the status register
     * @return uint8_t the status register
     */
    uint8_t readStatusReg(SR sr);
    /**
     * @brief Writes to the status register
     * @param sr the status register to write
     * @param value the value to write
     * @return bool true if the write was successful
     */
    bool writeStatusReg(SR sr, uint8_t value);
    /**
     * @brief Powers down the part
     * @return bool true if the part has shutdown
     */
    bool powerDown();
    /**
     * @brief Resets the part
     * @return bool true if the part is reset
     */
    bool reset();
    /**
     * @brief Gets the total size of the flash in megabits
     * @return uint32_t the size of the flash in bits
     */
    uint32_t getSize();
    /**
     * @brief Polls the flash to see if it is done writing/erasing
     * @return bool true if the memory is busy
     */
    bool isBusy();

private:
    bool sendCommand(uint8_t command);
    void setCommandAndAddress(uint8_t command, uint32_t address, uint8_t * buf);
    bool erase(uint8_t command, uint32_t address);


private:
    Embedded::Micro::Interface::ISPI    *_spi;
    Embedded::Micro::Interface::IGPIO   *_cs;
    Embedded::Micro::Interface::ITimer  *_timer;
};


} // namespace Winbond
} // namespace Memory
} // namespace Embedded


#endif // EMBEDDED_MEMORY_WINBOND_NORFLASH
