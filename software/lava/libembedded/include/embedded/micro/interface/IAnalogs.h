#ifndef EMBEDDED_MICRO_INTERFACE_ANALOGS_H_
#define EMBEDDED_MICRO_INTERFACE_ANALOGS_H_

#include <stdint.h>

namespace Embedded {
namespace Micro {
namespace Interface {

class IAnalogs
{
public:
    /**
     * Destructor
     *
     */
    virtual ~IAnalogs() {}

    /**
     * Function to get the converted AD channels, these are raw unfiltered AD conversions
     *
     * @param channel the channel to retrieve
     * @return uint16_t the raw 12-bit AD converted value
     */
    virtual uint16_t get(uint16_t rank) const = 0;
    /**
     * This function starts the AD conversion activities. The DMA will copy each channel as it
     * gets converted and moves it into RAM.
     *
     */
    virtual void start() = 0;
    /**
    * This function starts the converted in high speed DMA mode. Once the AD
    * is setup and the channels are configured for conversion, this function
    * will kick off a single DMA transfer of totalCovnersions. Once the total
    * conversions is complete, the conversation will stop. It is up to the
    * caller to call this function repeatedly.
    *
    * The conversion speed will be the APB2 clock / 8 / adcConversionRate
    * For example with an 84 MHz APB2 clock and a 480 cycle adcConversionRate
    * The conversion rate would be 4375 Hz
    *
    * @param totalConversions the number of conversations to transfer via DMA
    * @param buffer the buffer to store the samples in
    */
    virtual void start(uint16_t totalConversions, uint16_t * buffer) = 0;
    /**
     * This function stops the DMA and AD conversion activities
     *
     * @return returns the number of bytes remaining to be transferd in the DMA
     */
    virtual uint16_t stop() = 0;
    /**
     * This function gets the ADC over run flag. This flag will get set anytime the DMA
     * cannot move data out of the conversion register into the RAM holding area
     *
     */
    virtual bool overrun() = 0;
    /**
     * Returns the maximum signal the AD converted can return
     *
     * @return uint16_t the value of the maximum converted AD count
     */
    virtual uint16_t getMaxADCValue() const = 0;
    /**
     * Returns the internal VREF
     *
     * @return float the vref of the AD converter
     */
    virtual float getADCVRef() const = 0;
    /**
    * This function returns the ratiometrically correct voltage
    * based on the VREFInt signal.
    * The STM32F4 contains an internal VrefInt signal. This signal should
    * be a constant voltage regardless of the reference voltage used by the
    * AD converter. On the STM32F405 it is 1.18 to 1.24 volts with a typ value
    * of 1.21 volts.
    *
    * The normal equation to convert to get voltage is:
    * Voltage = ADReading / MaxADValue * VDDA
    *
    * This function takes the VRefInt reading and the AD value you want to convert
    * and performs the following operation
    *
    * VDDA = 1.21V * MaxADValue / VrefInt
    * Vratio = voltage / MaxADValue * VDDA
    *
    * @param VRefInt the converstion of the VrefInt signal
    * @param voltage the signal to convert
    * @param nominalVRef the nominal value to convert
    * @return T the converted value, this can be either float or double
    */
    float getRatiometricVoltage(uint16_t VRefIntADC, uint16_t voltage)
    {
        float vdda = getADCVRef();
        vdda *= getMaxADCValue();
        vdda /= VRefIntADC;
        return (voltage * vdda) / getMaxADCValue();
    }

protected:
    /**
     * Constructor
     */
    IAnalogs()  {}
};

} // Interface
} // Micro
} // Embedded

#endif /* EMBEDDED_MICRO_INTERFACE_ANALOGS_H_ */
