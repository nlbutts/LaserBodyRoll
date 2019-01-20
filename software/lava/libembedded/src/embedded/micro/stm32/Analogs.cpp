#include <cstring>
#include "embedded/micro/stm32/Analogs.h"

namespace Embedded {
namespace Micro {
namespace STM32 {

Analogs::Analogs(ADC_TypeDef * dev,
                 DMADriver &dma,
                 uint8_t adcConversionRate)
: _dev(dev)
, _dma(&dma)
, _currentRank(0)
, _adcConversionRate(adcConversionRate)
{
    ADC_CommonStructInit(&_cfgCommon);
    ADC_StructInit(&_cfgInit);
    ClockControl::enable(clock);
    memset(_channels, 0, sizeof(_channels));
}

Analogs::~Analogs()
{
    stop();
}

uint16_t Analogs::get(uint16_t rank) const
{
    if (rank < _currentRank)
    {
        return _channels[rank];
    }
    return 0;
}

void Analogs::start()
{
    /* Setup DMA */
    _dma->setTransferWidth(DMADriver::HALF_WORD);
    _dma->setBufferMode(DMADriver::CIRCULAR);
    _dma->setPeripheralToMemory();
    _dma->updatePtrs((uint32_t)&_dev->DR, (uint32_t)_channels, _currentRank);    /*lint !e534, !e641*/
    _dma->enableMemoryInc();
    _dma->start();                                                      /*lint !e534*/

    /* ADC Common Init **********************************************************/
    _cfgCommon.ADC_Mode = ADC_Mode_Independent;
    _cfgCommon.ADC_Prescaler = ADC_Prescaler_Div8;
    _cfgCommon.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
    _cfgCommon.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_20Cycles;    // don't care with single ADC
    ADC_CommonInit(&_cfgCommon);

    /* ADC3 Init ****************************************************************/
    _cfgInit.ADC_Resolution = ADC_Resolution_12b;
    _cfgInit.ADC_ScanConvMode = ENABLE;
    _cfgInit.ADC_ContinuousConvMode = ENABLE;
    _cfgInit.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
    _cfgInit.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
    _cfgInit.ADC_DataAlign = ADC_DataAlign_Right;
    _cfgInit.ADC_NbrOfConversion = _currentRank;                     //lint !e641
    ADC_Init(_dev, &_cfgInit);

    ADC_TempSensorVrefintCmd(ENABLE);

   /* Enable DMA request after last transfer (Single-ADC mode) */
    ADC_DMARequestAfterLastTransferCmd(_dev, ENABLE);

    /* Enable ADC3 DMA */
    ADC_DMACmd(_dev, ENABLE);

    /* Enable ADC3 */
    ADC_Cmd(_dev, ENABLE);

    _dev->SR &= ~ADC_FLAG_OVR;

    ADC_SoftwareStartConv(_dev);
}

void Analogs::start(uint16_t totalConversions, uint16_t * buffer)
{
    /* Setup DMA */
    _dma->setTransferWidth(DMADriver::HALF_WORD);
    _dma->setBufferMode(DMADriver::NORMAL);
    _dma->setPeripheralToMemory();
    _dma->updatePtrs((uint32_t)&_dev->DR, (uint32_t)buffer, totalConversions);    /*lint !e534, !e641*/
    _dma->enableMemoryInc();
    _dma->start();                                                      /*lint !e534*/

    /* ADC Common Init **********************************************************/
    _cfgCommon.ADC_Mode = ADC_Mode_Independent;
    _cfgCommon.ADC_Prescaler = ADC_Prescaler_Div8;
    _cfgCommon.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
    _cfgCommon.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;    // don't care with single ADC
    ADC_CommonInit(&_cfgCommon);

    /* ADC3 Init ****************************************************************/
    _cfgInit.ADC_Resolution = ADC_Resolution_12b;
    _cfgInit.ADC_ScanConvMode = ENABLE;
    _cfgInit.ADC_ContinuousConvMode = ENABLE;
    _cfgInit.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
    _cfgInit.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
    _cfgInit.ADC_DataAlign = ADC_DataAlign_Right;
    _cfgInit.ADC_NbrOfConversion = 1;                     //lint !e641
    ADC_Init(_dev, &_cfgInit);

   /* Enable DMA request after last transfer (Single-ADC mode) */
    ADC_DMARequestAfterLastTransferCmd(_dev, ENABLE);

    /* Enable ADC DMA */
    ADC_DMACmd(_dev, ENABLE);

    /* Enable ADC */
    ADC_Cmd(_dev, ENABLE);

    _dev->SR &= ~ADC_FLAG_OVR;

    ADC_SoftwareStartConv(_dev);
}

uint16_t Analogs::stop()
{
    uint16_t bytesRemaining = _dma->getBytesRemaining();
    ADC_Cmd(_dev, DISABLE);
    _dma->stop();
    return bytesRemaining;
}

void Analogs::registerAllNormalChannels()
{
    for (uint16_t i = 0; i < Analogs::MaxConversionChannels; ++i)
    {
        ADC_RegularChannelConfig(_dev, i, i + 1, _adcConversionRate);
    }
    _currentRank = Analogs::MaxConversionChannels;
}

bool Analogs::pushChannelOrder(ADCChannels channel)
{
    bool rv = true;
    if (_currentRank == Analogs::MaxConversionChannels)
    {
        rv = false;
    }
    else
    {
        ADC_RegularChannelConfig(_dev, channel, _currentRank + 1, _adcConversionRate);
        _currentRank++;
    }
    return rv;
}

} // namespace Embedded
} // namespace Micro
} // namespace STM32
