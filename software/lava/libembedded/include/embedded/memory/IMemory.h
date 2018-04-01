#ifndef EMBEDDED_MEMORY_IMEMORY_H_
#define EMBEDDED_MEMORY_IMEMORY_H_

#include <stdint.h>

namespace Embedded {
namespace Memory {

/**
 * @brief This is an interface class for a memory device
**/
class IMemory
{
public:
    /**
     * @brief Destructor
     */
    virtual ~IMemory()  {};
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
    virtual bool readData(uint32_t address, uint8_t * buf, uint32_t len) = 0;
    /**
     * @brief Writes data to the memory device
     * @details The implementer of this function will have to handle erases
     * and writes.
     *
     * @param address the address to write data
     * @param buf a pointer to the buffer to store the return data
     * @param len the number of bytes to read
     * @return bool true if the write was succesful
     */
    virtual bool writeDataPoll(uint32_t address, uint8_t * buf, uint32_t len) = 0;
    /**
     * @brief This function will erase a block and poll to see if the erase is complete
     * @details When this function is first called, if the flash is not busy it will erase it
     * and return, future calls to this function will check if it is busy
     *
     * @param address the address to erase
     * @return bool true if the erase is complete
     */
    virtual bool eraseSubsectorPoll(uint32_t address) = 0;
    /**
     * @brief Gets the total size of the flash in megabits
     * @return uint32_t the size of the flash in bits
     */
    virtual uint32_t getSize() = 0;
    /**
     * @brief Get page size
     * @return uint32_t the page size of this memory device
     */
    virtual uint32_t getPageSize() = 0;
    /**
     * @brief Get the minimum erase size for this part
     * @return uint32_t the page size of this memory device
     */
    virtual uint32_t getMinEraseSize() = 0;
    /**
     * @brief Polls the flash to see if it is done writing/erasing
     * @return bool true if the memory is busy
     */
    virtual bool isBusy() = 0;

protected:
    IMemory()   {};
};


} // namespace Memory
} // namespace Embedded


#endif // EMBEDDED_MEMORY_IMEMORY_H_
