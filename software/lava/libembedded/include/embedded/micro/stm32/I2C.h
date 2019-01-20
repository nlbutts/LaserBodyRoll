#ifndef EMBEDDED_MICRO_STM32F4_I2C_H_
#define EMBEDDED_MICRO_STM32F4_I2C_H_

#include "embedded/micro/interface/II2C.h"
#include "embedded/micro/stm32/GPIO.h"
#include "embedded/micro/stm32/Timer.h"

namespace Embedded {
namespace Micro {
namespace STM32 {

enum I2C_CHANNELS
{
   I2C_CH1A,
   I2C_CH1B,
   I2C_CH2A,
   I2C_CH2B,
   I2C_CH3A,
   I2C_CH3B,
};

class I2C : public Embedded::Micro::Interface::II2C
{
    public:
        enum I2C_CR1
        {
            PE,             // 0
            SMBUS,          // 1
            RES,            // 2
            SMB_TYPE,       // 3
            ENARP,          // 4
            ENPEC,          // 5
            ENGC,           // 6
            NO_STRETCH,     // 7
            START,          // 8
            STOP,           // 9
            ACK,            // 10
            POS,            // 11
            PEC,            // 12
            ALERT,          // 13
            RES2,           // 14
            SWRST           // 15
        };

        /**
         * @brief Class constructor
         * @detail Before creating this class make sure the RCC clock has been enabled
         *
         * @param dev pointer to the I2C device hardware
         * @param sclPort which port to use for SCL
         * @param sclPin which pin to use for SCL
         * @param sdaPort which port to use for SDA
         * @param sdaPin which pin to use for SDA
         */
        I2C(I2C_TypeDef * dev,
            GPIO::GPIO_PORTS sclPort,
            GPIO::GPIO_PINS sclPin,
            GPIO::GPIO_PORTS sdaPort,
            GPIO::GPIO_PINS sdaPin);
        virtual ~I2C();

        /**
         * This generic function allows multiple bytes to be written to an I2C device. This function
         * can terminate the I2C transaction or leave the bus idle after the write is complete
         * This is blocking write
         *
         * @param i2cAddr the devices I2C address
         * @param buf pointer to a buffer of data that will be written
         * @param len the length of data to write
         * @param genStop true if this write should terminate with a stop condition, otherwise it will leave the bus idle
         * @return bool true if the write was successful, false otherwise
         */
        bool write(uint8_t i2cAddr, const uint8_t * buf, uint16_t len, bool genStop);
        /**
         * This is a helper function that makes it easy to call a write to an I2C device
         * that supports the concept of a sub-address, followed by the data to be written
         * to the sub-address
         * This is blocking write
         *
         * @param i2cAddr the devices I2C address
         * @param reg the sub address to write to
         * @param val the value to write at the sub-address
         * @return bool true if the write was successful, false otherwise
         */
        bool write(uint8_t i2cAddr, uint8_t reg, uint8_t val);
        /**
         * The read and write functions above do not work with the MFi chip. This function
         * is a very simple single byte write function. It writes the I2C address and then reg
         *          *
         * @param i2cAddr the I2C address of the device
         * @param reg the value to write, probably a bad name
         * @param genStop true if this write should terminate with a stop condition, otherwise it will leave the bus idle
         * @return bool true if the write was successful, false otherwise
         */
        bool  write(uint8_t i2cAddr, uint8_t reg, bool genStop);
        /**
         * This function sends a read register and then reads len bytes into buf
         * This is a blocking read
         *
         * @param i2cAddr the 7-bit I2C address of the device to communicate with
         * @param buf a pointer to a buffer that is large enough to hold len bytes of data
         * @param len the number of bytes to read
         * @return bool true if the read completed successfully, false otherwise
         */
        bool read(uint8_t i2cAddr, uint8_t *buf, uint8_t len);
        /**
         * Helper function to perform a write to select sub-address reg followed by a read of
         * that value
         *
         * @param i2cAddr the I2C address of the device
         * @param reg the sub-address to write to the I2C device
         * @return int16_t a negative number if the write failes, otherwise the actual value read
         */
        int16_t read(uint8_t i2cAddr, uint8_t reg);
        /**
         * This function sends the I2C address with a read request and reads a single byte.
         *
         * @param i2cAddr the I2C address of the device
         * @return int16_t a negative number if the write failes, otherwise the actual value read
         */
        int16_t read(uint8_t i2cAddr);

    private:
        /**
         * Configures the I2C pins
         *
         * @param sclPort the SCL port
         * @param sclPin the SCL pin
         * @param sdaPort the SDA port
         * @param sdaPin the SDA pin
         * @param clock the GPIO clock bank
         */
        void initPins(GPIO::GPIO_PORTS sclPort, GPIO::GPIO_PINS sclPin, GPIO::GPIO_PORTS sdaPort, GPIO::GPIO_PINS sdaPin) const;
        /**
         * Enable the RX Interrupts
         */
        void rxInterruptEnable( void );         /* Enable Rx interrupts */
        /**
         * Enable the TX Interrupts
         */
        void txInterruptEnable( void );         /* Enable tx interrupts */
        /**
         * This function is used to automate waiting on a I2C FLAG, this function will most likey
         * be deprecated in future releases
         */
        //bool waitFlag(uint32_t flag, FlagStatus waitWhileStatusIs);
        /**
         * This function is used to automate waiting on a I2C FLAG, this function will most likey
         * be deprecated in future releases
         */
        //bool waitEvent(uint32_t event);
        /**
         * This function attempts to get the I2C bus back in a good state. First it resets
         * the I2C controller, then it tries doing a single byte read and NACKs the packet.
         */
        void resetBus();
        /**
         * This is a shortcut function to set a bit in the CR1 register
         * @param bit the bit to set, this is an offset not a mask
         */
        void set(I2C_CR1 bit);
        /**
         * This is a shortcut function to clear a bit in the CR1 register
         * @param bit the bit to set, this is an offset not a mask
         */
        void clear(I2C_CR1 bit);
        /**
         * Generate a start event
         */
        void generateStart();
        /**
         * Generate a stop event
         */
        void generateStop();
        /**
         * Send an I2C address, this is actually the 8-bits that are sent in the address cycle
         * @param i2cAddr the full 8-bits to send
         * @return bool true if the write succeeded, false otherwise
         */
        bool sendAddr(uint8_t i2cAddr);
        /**
         * write a single byte via I2C
         * @param val the value to write
         * @return bool true if the write succeeded, false otherwise
         */
        bool writeByte(uint8_t val);
        /**
         * Reads a single byte on the bus, this function seems to time out and doesn't exit gracefully
         * TODO fix the timeout problem
         * @return int16_t a negative value if the read failured, otherwise returns the value
         */
        int16_t readByte();

        /**
        * Sets the speed of the I2C bus
        *
        * @param desiredSpeed the desired speed in Hz
        * @return uint32_t the actual speed in Hz
        */
        uint32_t setSpeed(uint32_t desiredSpeed);

        /*** Private Fields ***/
        static const uint32_t Timeout = 100;        // Timeout in ST boogy units (not defined)

        I2C_TypeDef         *_dev;                  // pointer to the I2C HW registers
        I2C_InitTypeDef     _cfg;                   // I2C configuration
        I2C_HandleTypeDef   _i2c;
        uint32_t            _moduleClock;           // The clock speed of I2C interface
        Timer               _timer;                 // Timer used to timeout I/O attempts

};

// template <I2C_CHANNELS T> class I2CDriverA;

// template <> class I2CDriverA<I2C_CH1A>  : public I2C {public: I2CDriverA() :
//     I2C(I2C1, GPIO::PORTB, GPIO::Pin_6, GPIO::PORTB, GPIO::Pin_7, ClockControl::I2C1CLK, GPIO::AF_4){};};
// template <> class I2CDriverA<I2C_CH1B>  : public I2C {public: I2CDriverA() :
//     I2C(I2C1, GPIO::PORTB, GPIO::Pin_8, GPIO::PORTB, GPIO::Pin_9, ClockControl::I2C1CLK, GPIO::AF_4){};};
// template <> class I2CDriverA<I2C_CH2A>  : public I2C {public: I2CDriverA() :
//     I2C(I2C2, GPIO::PORTH, GPIO::Pin_4, GPIO::PORTH, GPIO::Pin_5, ClockControl::I2C2CLK, GPIO::AF_4){};};
// template <> class I2CDriverA<I2C_CH2B>  : public I2C {public: I2CDriverA() :
//     I2C(I2C2, GPIO::PORTB, GPIO::Pin_10, GPIO::PORTB, GPIO::Pin_11, ClockControl::I2C2CLK, GPIO::AF_4){};};
// template <> class I2CDriverA<I2C_CH3A>  : public I2C {public: I2CDriverA() :
//     I2C(I2C3, GPIO::PORTH, GPIO::Pin_7, GPIO::PORTH, GPIO::Pin_8, ClockControl::I2C3CLK, GPIO::AF_4){};};
// template <> class I2CDriverA<I2C_CH3B>  : public I2C {public: I2CDriverA() :
//     I2C(I2C3, GPIO::PORTA, GPIO::Pin_8, GPIO::PORTC, GPIO::Pin_9, ClockControl::I2C3CLK, GPIO::AF_4){};};

} // namespace Embedded
} // namespace Micro
} // namespace STM32

#endif /* EMBEDDED_MICRO_STM32F4_I2C_H_ */
