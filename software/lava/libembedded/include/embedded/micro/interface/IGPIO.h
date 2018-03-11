#ifndef EMBEDDED_MICRO_INTERFACE_IGPIO_H_
#define EMBEDDED_MICRO_INTERFACE_IGPIO_H_

namespace Embedded {
namespace Micro {
namespace Interface {

/**
 * @brief Interface class for GPIO (General Purpose I/O)
 */
class IGPIO
{
public:
    virtual ~IGPIO() {}

    /*
     * Set the GPIO output to high. This will only succeed if the GPIO
     * was previously configured as an output.
     */
    virtual void set() = 0;

    /*
     * Set the GPIO output to low. This will only succeed if the GPIO
     * was previously configured as an output.
     */
    virtual void clear() = 0;

    /*
     * Toggles the state of the GPIO output. This will only succeed if the GPIO
     * was previously configured as an output.
     */
    virtual void toggle() = 0;

    /**
     * Gets the state of the GPIO pin
     */
    virtual bool get() const = 0;

    /**
     * Sets the GPIO output state. This will only succeed if the GPIO
     * was previously configured as an output.
     *
     * @param in 0 to set IO low, else high
     */
    virtual void operator = (const uint32_t in) = 0;

protected:
    IGPIO() {}
};


} // namespace Interface
} // namespace Micro
} // namespace Embedded

#endif /* EMBEDDED_MICRO_INTERFACE_IGPIO_H_ */