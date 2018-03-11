#ifndef EMBEDDED_MICRO_STM32_GPIO_H_
#define EMBEDDED_MICRO_STM32_GPIO_H_

#include <libst_config.h>
#include <embedded/micro/interface/IGPIO.h>

namespace Embedded {
namespace Micro {
namespace STM32 {

class GPIO : public Embedded::Micro::Interface::IGPIO
{
    public:
        typedef enum
        {
            PORTA,
            PORTB,
            PORTC,
            PORTD,
            PORTE,
            PORTF,
            PORTG,
            PORTH,
        } GPIO_PORTS;

        typedef enum
        {
            Pin_0,
            Pin_1,
            Pin_2,
            Pin_3,
            Pin_4,
            Pin_5,
            Pin_6,
            Pin_7,
            Pin_8,
            Pin_9,
            Pin_10,
            Pin_11,
            Pin_12,
            Pin_13,
            Pin_14,
            Pin_15,
        } GPIO_PINS;

        typedef enum
        {
            IN,
            OUT,
            ALTERNATE_FUNCTION,
            ANALOG,
        } GPIO_MODE;

        typedef enum
        {
            PUSH_PULL,
            OPEN_DRAIN,
        } GPIO_OTYPE;

        typedef enum
        {
            SLOW_2MHZ,
            MEDIUM_25MHZ,
            FAST_50MHZ,
            SUPER_100MHZ,
        } GPIO_SPEED;

        typedef enum
        {
            NO_PULL,
            PULL_UP,
            PULL_DOWN,
        } GPIO_RESISTOR;

        typedef enum
        {
            AF_0,
            AF_1,
            AF_2,
            AF_3,
            AF_4,
            AF_5,
            AF_6,
            AF_7,
            AF_8,
            AF_9,
            AF_10,
            AF_11,
            AF_12,
            AF_13,
            AF_14,
            AF_15,
        } AF_BANK;

        /**
         * This is the basic GPIO Initialization, it will create one output pin
         *
         * @param port the GPIO port
         * @param pin the GPIO pin 0-15
         * @param true if the output should start on, false otherwise
         */
        GPIO(GPIO_PORTS port, GPIO_PINS pin, bool outputOn);
        /**
         * This is the basic GPIO Initalization, it will create one input pin
         *
         * @param port the GPIO port
         * @param pin the GPIO pin 0-15
         * @param pullUpDown configure the port to use a pull up, pull down, or none
         */
        GPIO(GPIO_PORTS port, GPIO_PINS pin, GPIO_RESISTOR pullUpDown);
        /**
         * This is the full featured GPIO initialization, it allows full control over a pin
         *
         *
         * @param port the GPIO port
         * @param pin the GPIO pin 0-15
         * @param mode the mode, GPIO_Mode_In, GPIO_Mode_Out, GPIO_Mode_AF, GPIO_Mode_AN
         * @param outputType GPIO_OType_PP (push pull) or GPIO_OType_OD (open drain)
         * @param speed GPIO_Speed_2MHz, GPIO_Speed_25MHz, GPIO_Speed_50MHz, GPIO_Speed_100MHz
         * @param pullUpDown GPIO_PuPd_NOPULL, GPIO_PuPd_UP, GPIO_PuPd_DOWN
         * @param AF if alternate function is selected, this values configures the AF
         */
        GPIO(GPIO_PORTS port, GPIO_PINS pin, GPIO_MODE mode, GPIO_OTYPE outputType, GPIO_SPEED speed, GPIO_RESISTOR pullUpDown, AF_BANK AF);
        GPIO(GPIO_PORTS port, GPIO_PINS pin, GPIO_MODE mode, GPIO_OTYPE outputType, GPIO_SPEED speed, GPIO_RESISTOR pullUpDown, AF_BANK AF, bool outputOn);
        GPIO(GPIO_PORTS port, GPIO_PINS pin, AF_BANK AF);
        GPIO(GPIO_PORTS port, GPIO_PINS pin, GPIO_MODE mode);
        //virtual ~GPIO();

        inline void set()       { _port->BSRR = _mask; }
        inline void clear()     { _port->BSRR = _mask << 16; }
        inline void toggle()    { get() ? clear() : set(); }
        inline bool get() const { return static_cast<bool>(_port->IDR & _mask); }

        inline void operator = (const uint32_t in)
        {
            if (in)
                set();
            else
                clear();
        }

    private:
        GPIO_TypeDef*       _port;
        GPIO_PINS           _configPin;
        uint16_t            _mask;
        GPIO_InitTypeDef    _gpioStruct;

        /**
         * Enables the clock for this GPIO module
         *
         */
        void enableClock();
        /**
         * Configures the GPIO pins
         *
         * @param mode the mode, GPIO_Mode_In, GPIO_Mode_Out, GPIO_Mode_AF, GPIO_Mode_AN
         * @param outputType GPIO_OType_PP (push pull) or GPIO_OType_OD (open drain)
         * @param speed GPIO_Speed_2MHz, GPIO_Speed_25MHz, GPIO_Speed_50MHz, GPIO_Speed_100MHz
         * @param pullUpDown GPIO_PuPd_NOPULL, GPIO_PuPd_UP, GPIO_PuPd_DOWN
         * @param AF the alternate function to be used with this pin
         */
        void configPins(GPIO_MODE mode, GPIO_OTYPE outputType, GPIO_SPEED speed, GPIO_RESISTOR pullUpDown, AF_BANK AF);

};

} // namespace STM32
} // namespace Micro
} // namespace Embedded

#endif /* EMBEDDED_MICRO_STM32_GPIO_H_ */
