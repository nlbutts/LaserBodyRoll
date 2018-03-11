#include <embedded/micro/stm32/GPIO.h>

using Embedded::Micro::STM32::GPIO;

/*lint -e1773 */
/*lint -e1566 */

static const GPIO_TypeDef * const GPIOEnumToPtr[] =
{
    GPIOA,  /*lint !e835*/
    GPIOB,
    GPIOC,
    GPIOD,
    GPIOE,
    GPIOF,
    GPIOG,
    GPIOH,
};

GPIO::GPIO(GPIO_PORTS port, GPIO_PINS pin, bool outputOn)
: _port((GPIO_TypeDef*)GPIOEnumToPtr[port])
, _configPin(pin)
, _mask(static_cast<uint16_t>(1U << static_cast<int>(_configPin)))
{
    enableClock();
    if (outputOn)
    {
        set();
    }
    else
    {
        clear();
    }
    configPins(OUT, PUSH_PULL, SLOW_2MHZ, NO_PULL, AF_BANK::AF_0);
}


GPIO::GPIO(GPIO_PORTS port, GPIO_PINS pin, GPIO_RESISTOR pullUpDown)
: _port((GPIO_TypeDef*)GPIOEnumToPtr[port])
, _configPin(pin)
, _mask(static_cast<uint16_t>(1U << static_cast<int>(_configPin)))
{
    enableClock();
    configPins(IN, PUSH_PULL, SLOW_2MHZ, pullUpDown, AF_BANK::AF_0);
    clear();
}

GPIO::GPIO(GPIO_PORTS port, GPIO_PINS pin, GPIO_MODE mode, GPIO_OTYPE outputType, GPIO_SPEED speed, GPIO_RESISTOR pullUpDown, AF_BANK AF)
: _port((GPIO_TypeDef*)GPIOEnumToPtr[port])
, _configPin(pin)
, _mask(static_cast<uint16_t>(1U << static_cast<int>(_configPin)))
{
    enableClock();
    configPins(mode, outputType, speed, pullUpDown, AF);
}

GPIO::GPIO(GPIO_PORTS port, GPIO_PINS pin, GPIO_MODE mode, GPIO_OTYPE outputType, GPIO_SPEED speed, GPIO_RESISTOR pullUpDown, AF_BANK AF, bool outputOn)
: _port((GPIO_TypeDef*)GPIOEnumToPtr[port])
, _configPin(pin)
, _mask(static_cast<uint16_t>(1U << static_cast<int>(_configPin)))
{
    enableClock();
    if (outputOn)
    {
        set();
    }
    else
    {
        clear();
    }
    configPins(mode, outputType, speed, pullUpDown, AF);
}

GPIO::GPIO(GPIO_PORTS port, GPIO_PINS pin, AF_BANK AF)
: _port((GPIO_TypeDef*)GPIOEnumToPtr[port])
, _configPin(pin)
, _mask(static_cast<uint16_t>(1U << static_cast<int>(_configPin)))
{
    enableClock();
    configPins(ALTERNATE_FUNCTION, PUSH_PULL, MEDIUM_25MHZ, NO_PULL, AF);
}

GPIO::GPIO(GPIO_PORTS port, GPIO_PINS pin, GPIO_MODE mode)
: _port((GPIO_TypeDef*)GPIOEnumToPtr[port])
, _configPin(pin)
, _mask(static_cast<uint16_t>(1U << static_cast<int>(_configPin)))
{
    enableClock();
    configPins(mode, PUSH_PULL, MEDIUM_25MHZ, NO_PULL, AF_BANK::AF_0);
}

/*lint -e1762 */
void GPIO::enableClock()
{
    //ClockControl::RCC_CLOCK peripherialClock = ClockControl::UNDEFINED;
    switch ((uint32_t)_port)
    {
        case GPIOA_BASE: /*lint !e835 */
            __HAL_RCC_GPIOA_CLK_ENABLE();
            break;
        case GPIOB_BASE:
            __HAL_RCC_GPIOB_CLK_ENABLE();
            break;
        case GPIOC_BASE:
            __HAL_RCC_GPIOC_CLK_ENABLE();
            break;
        case GPIOD_BASE:
            __HAL_RCC_GPIOD_CLK_ENABLE();
            break;
        case GPIOF_BASE:
            __HAL_RCC_GPIOF_CLK_ENABLE();
            break;
        default:
            break;
    }
}

void GPIO::configPins(GPIO_MODE mode, GPIO_OTYPE outputType, GPIO_SPEED speed, GPIO_RESISTOR pullUpDown, AF_BANK AF)
{
    _gpioStruct.Pin         = _mask;
    _gpioStruct.Mode        = (uint32_t)mode;
    _gpioStruct.Speed       = (uint32_t)speed;
    _gpioStruct.Pull        = (uint32_t)pullUpDown;
    _gpioStruct.Alternate   = AF;
    HAL_GPIO_Init(_port, &_gpioStruct);
}
