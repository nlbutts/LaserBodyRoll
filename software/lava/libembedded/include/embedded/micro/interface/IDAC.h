#ifndef EMBEDDED_MICRO_INTERFADACOGS_H_
#define EMBEDDED_MICRO_INTERFADACOGS_H_

#include <stdint.h>

namespace Embedded {
namespace Micro {
namespace Interface {

class IDAC
{
public:
    /**
     * Destructor
     *
     */
    virtual ~IDAC() {}

    /**
     * @brief This function returns the current output voltage in volts
     * @return float output voltage in volts
     */
    virtual float get() const = 0;
    /**
     * @brief This functions sets the DAC output voltages in volts and returns the actual voltage
     *
     * @param voltage the desired voltage in volts
     * @return The actual output voltage in volts
     */
    virtual float set(float voltage) = 0;

protected:
    /**
     * Constructor
     */
    IDAC()  {}
};

} // Interface
} // Micro
} // Embedded

#endif /* EMBEDDED_MICRO_INTERFACE_DAC_H_ */
