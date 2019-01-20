#ifndef EMBEDDED_MICRO_STM32F4_ANALOGS_H_
#define EMBEDDED_MICRO_STM32F4_ANALOGS_H_

#include "libst_conf.h"
#include "appareo/micro/interface/IAnalogs.h"
//#include "appareo/micro/stm32/ClockControl.h"
#include "appareo/micro/stm32/DMA.h"

namespace Embedded {
namespace Micro {
namespace STM32 {

class Analogs : public Appareo::Micro::Interface::IAnalogs
{
public:
    typedef enum
    {
        CHANNEL_0,
        CHANNEL_1,
        CHANNEL_2,
        CHANNEL_3,
        CHANNEL_4,
        CHANNEL_5,
        CHANNEL_6,
        CHANNEL_7,
        CHANNEL_8,
        CHANNEL_9,
        CHANNEL_10,
        CHANNEL_11,
        CHANNEL_12,
        CHANNEL_13,
        CHANNEL_14,
        CHANNEL_15,
        CHANNEL_16,
        CHANNEL_17,
        CHANNEL_18,
        MAX
    } ADCChannels;

    /**
     * Constructor to setup an ADC module
     *
     * @param dev a pointer to the AD device (there are three of them on this processor
     * @param dma a reference to a DMA module that will be used to move the ADC
     * @param adcConversionRate the rate at which the AD converts data
     */
    Analogs(ADC_TypeDef * dev, DMADriver &dma, uint8_t adcConversionRate = ADC_SampleTime_480Cycles);
    /**
     * Destructor
     *
     */
    virtual ~Analogs();

    /**
     * Function to get the converted AD channels, these are raw unfiltered AD conversions
     *
     * @param channel the channel to retrieve
     * @return uint16_t the raw 12-bit AD converted value
     */
    uint16_t get(uint16_t rank) const;
    /**
     * This function starts the AD conversion activities. The DMA will copy each channel as it
     * gets converted and moves it into RAM.
     *
     */
    void start();
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
    void start(uint16_t totalConversions, uint16_t * buffer);
    /**
     * This function stops the DMA and AD conversion activities
     *
     * @return returns the number of bytes remaining to be transferd in the DMA
     */
    uint16_t stop();
    /**
     * This function gets the ADC over run flag. This flag will get set anytime the DMA
     * cannot move data out of the conversion register into the RAM holding area
     *
     */
    bool overrun()  {return (bool)(_dev->SR & ADC_FLAG_OVR);}
    /**
     * Returns the maximum signal the AD converted can return
     *
     * @return uint16_t the value of the maximum converted AD count
     */
    uint16_t getMaxADCValue() const     {return 4095;}
        /**
     * Returns the internal VREF
     *
     * @return float the vref of the AD converter
     */
    float getADCVRef() const         {return Analogs::VrefInt;}
    /**
    * This function pushes the AD conversion channel order. If left
    * to the defaults, it will convert channels 0-15 in that order. This
    * function allows you to specify which channels to convert and how many
    * to convert.
    *
    * For example, you could call this function like this:
    * pushChannelOrder(CHANNEL_0)
    * pushChannelOrder(CHANNEL_1)
    * pushChannelOrder(CHANNEL_0)
    * pushChannelOrder(CHANNEL_2)
    * pushChannelOrder(CHANNEL_0)
    * pushChannelOrder(CHANNEL_3)
    *
    * This would convert channel 0 every other conversion
    *
    * @param channel - which channel to convert next
    * @return bool true if the push was successful, false otherwise
    */
    bool pushChannelOrder(ADCChannels channel);
    /**
     * Registers all "normal" AD channels from 0 to 15. This will
     * not register the internal temperature sensor or the VREFINT.
     */
    void registerAllNormalChannels();

private:
    /**
     * filters the AD Channels
     */
    void filterChannels();

    static constexpr uint16_t MaxConversionChannels = 16;
    static constexpr double VrefInt                 = 1.21;

    ADC_TypeDef *           _dev;
    DMADriver *             _dma;       /*lint -e1540 */
    uint16_t                _currentRank;
    uint8_t                 _adcConversionRate;
    uint16_t                _channels[MAX];
    ADC_CommonInitTypeDef   _cfgCommon;
    ADC_InitTypeDef         _cfgInit;
};

} // namespace STM32
} // namespace Micro
} // namespace Embedded

#endif /* EMBEDDED_MICRO_STM32F4_ANALOGS_H_ */
