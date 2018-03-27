
#include <algorithm>
#include "embedded/micro/stm32/DigitalToAnalog.h"

namespace Embedded {
namespace Micro {
namespace STM32 {

DigitalToAnalog::DigitalToAnalog(DAC_HandleTypeDef &hdac1, DACChannels channel, float vref)
: _dac(&hdac1)
, _channel(channel)
, _vref(vref)
{
    HAL_DAC_Start(_dac, _channel);
}

DigitalToAnalog::~DigitalToAnalog()
{
}

float DigitalToAnalog::set(float voltage)
{
    float temp = ((voltage / _vref) * maxSignal()) + 0.5f;
    uint16_t data = static_cast<uint16_t>(temp);
    data = std::min(data, maxSignal());
    float rv = (static_cast<float>(data) / 4095.0f) * _vref;
    _currentOutputVoltage = rv;
    if (_channel == CHANNEL_0)
    {
        HAL_DAC_SetValue(_dac, _channel,  DAC_ALIGN_12B_R, data);
    }
    else
    {
        HAL_DAC_SetValue(_dac, _channel,  DAC_ALIGN_12B_R, data);
    }
    return rv;
}

}
}
}
