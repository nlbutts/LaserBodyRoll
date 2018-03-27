#ifndef EMBEDDED_MICRO_STM32_DIGITALTOANALOG_H_
#define EMBEDDED_MICRO_STM32_DIGITALTOANALOG_H_

#include "libst_config.h"
#include "embedded/micro/interface/IDAC.h"

namespace Embedded {
namespace Micro {
namespace STM32 {

class DigitalToAnalog : public Embedded::Micro::Interface::IDAC
{
public:
    typedef enum
    {
        CHANNEL_0 = DAC_CHANNEL_1,
        CHANNEL_1 = DAC_CHANNEL_2
    } DACChannels;

    /**
     * Constructor to setup an ADC module
     *
     * @param clock which clock to use when setting up the ADC
     * @param channel which channel to drive
     * @param vref the reference voltage for the AD and DAC
     */
    DigitalToAnalog(DAC_HandleTypeDef &hdac1, DACChannels channel, float vref);
    /**
     * Destructor
     *
     */
    virtual ~DigitalToAnalog();

    /**
    * @brief This function returns the current output voltage in volts
    * @return float output voltage in volts
    */
    float get() const   {return _currentOutputVoltage;}
    /**
    * @brief This functions sets the DAC output voltages in volts and returns the actual voltage
    *
    * @param voltage the desired voltage in volts
    * @return The actual output voltage in volts
    */
    float set(float voltage);
    /**
     * Returns the maximum signal the DAC converted can return
     *
     * @return uint16_t the value of the maximum converted AD count
     */
    uint16_t maxSignal() const      {return 4095;}

private:
    DAC_HandleTypeDef      *_dac;
    DACChannels             _channel;
    float                   _vref;
    float                   _currentOutputVoltage;
};

} // namespace Embedded
} // namespace Micro
} // namespace STM32

#endif /* EMBEDDED_MICRO_STM32_DIGITALTOANALOG_H_ */
