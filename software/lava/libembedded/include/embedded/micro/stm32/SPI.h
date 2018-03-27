#ifndef EMBEDDED_MICRO_STM32_SPI_H_
#define EMBEDDED_MICRO_STM32_SPI_H_

#include "libst_config.h"
#include "embedded/micro/stm32/DMA.h"
#include "embedded/micro/interface/ISPI.h"

namespace Embedded {
namespace Micro {
namespace STM32 {

typedef enum
{
    SPI_CH1,
    SPI_CH2,
    SPI_CH3
} SPI_CHANNELS;

class SPI : public Appareo::Micro::Interface::ISPI
{
    public:
        typedef enum
        {
            FPCLK_DIV2      = SPI_BaudRatePrescaler_2,
            FPCLK_DIV4      = SPI_BaudRatePrescaler_4,
            FPCLK_DIV8      = SPI_BaudRatePrescaler_8,
            FPCLK_DIV16     = SPI_BaudRatePrescaler_16,
            FPCLK_DIV32     = SPI_BaudRatePrescaler_32,
            FPCLK_DIV64     = SPI_BaudRatePrescaler_64,
            FPCLK_DIV128    = SPI_BaudRatePrescaler_128,
            FPCLK_DIV256    = SPI_BaudRatePrescaler_256,
        } SPI_BR;

        /**
         * @brief Constructor for DMA-less SPI
         * @details DMA based functions will not succeed if this
         *          constructor is used
         *
         * @param spiBase Base peripheral to use
         */
        SPI(SPI_TypeDef * spiBase);

        /**
         * @brief Constructor for DMA based SPI
         * @details DMA based transfer and normal blocking transfers will both work
         *
         * @param spiBase Base peripheral to use
         * @param clock Clock for the base peripheral
         * @param txDMA Transmit DMA object
         * @param rxDMA Receive DMA object.
         */
        SPI(SPI_TypeDef * spiBase, DMADriver &txDMA, DMADriver &rxDMA);
        virtual ~SPI();

        /**
         * This function is used to read data from the SPI interface. This function will
         * send out a 0 for every byte that is read in. This is a blocking function.
         *
         * @param ptr Pointer to the receive character buffer.
         *            Must be at least len bytes long
         * @param len Number of bytes to read into the rx buffer.
         */
        void read(uint8_t * rx, uint16_t len);

        /**
         * Writes data to the SPI port, this function blocks until the data is transmitted.
         *
         * @param tx Pointer to the transmit data buffer. Must not be NULL.
         * @param len Length of the data to transmit
         * @return Number of bytes transmitted or 0 if a transfer failed
         */
        uint16_t write(const uint8_t * tx, uint16_t len);

        /**
         * Writes data to the SPI port, this function blocks until the data is transmitted.
         *
         * @param tx Pointer to the transmit data buffer. Must not be NULL. The buffer must
         *           be at least len bytes long.
         * @param rx Pointer to the receive data buffer. Must be NULL, or at least
         *           len bytes long.
         * @param len Length of the data to transmit
         * @return Number of bytes transmitted or 0 if a transfer failed
         */
        uint16_t write(const uint8_t * tx, uint8_t * rx, uint16_t len);

        /**
         * Flushes the DMA drivers. This call blocks until all data has been transmitted
         */
        void flushDMA();

        /**
         * Setup and initiate a transmit DMA system. These functions do not block. The
         * isDMAInProgress() function can be used to determine when the transfer is finished.
         *
         * @param tx Pointer to the data to transmit. Must not be NULL.
         * @param rx Pointer to the data to receive or NULL
         * @param len Length of data to transmit
         * @return true if the DMA was setup correctly, else false
         */
        bool writeDMA(const uint8_t * tx, uint8_t * rx, uint16_t len);

        /**
         * This functions checks if a previous writeDMA() has completed.
         *
         * @return true if any Tx or Rx DMA's are in progress
         */
        bool isDMAInProgress();

        /**
         * @brief Configures the SPI module
         *
         * @param master true for master mode, false for slave mode
         * @param size8b true for 8 bit data, false for 16 bit
         * @param CPOLhigh true for clock idle polarity high, false for clock idle polarity low
         * @param CPHAedge1 true for bit sampling on rising edge, false for bit sampling on falling edge
         * @param msbFirst true for MSBit transmit first
         */
        void setupSPI(bool master, bool size8b, bool CPOLhigh, bool CPHAedge1, bool msbFirst);

        /**
         * Sets the SPI Clock frequency, this function will search through to find the
         * prescaler that will generate an SPI clock rate less than or equal to the
         * frequency requested. This may generate a clock rate significantly lower than
         * you expect. Be careful.
         *
         * @param frequency the frequency in Hz
         * @return the actual SPI frequency
         */
        uint32_t setFrequency(uint32_t frequency);

        /**
         * Sets the baud rate divider
         *
         * @param divider an enum for the divider
         */
        void setDivider(SPI_BR divider);

    private:
        /*** Private Fields ***/
        SPI_TypeDef         *_dev;
        DMADriver           *_txDMA;
        DMADriver           *_rxDMA;
        SPI_InitTypeDef     _spiCfg;
        uint32_t            _fpclk;

        /*** Private Methods ***/
        void rxInterruptEnable( void );         /* Enable Rx interrupts */
        void txInterruptEnable( void );         /* Enable tx interrupts */
        void setupInputClock();

        void emptyRxQueue(void);

};

template <SPI_CHANNELS T> class SPIDriverA;

template <> class SPIDriverA<SPI_CH1>  : public SPI {public: SPIDriverA() :
    SPI(SPI1, ClockControl::SPI1CLK){};};

template <> class SPIDriverA<SPI_CH2>  : public SPI {public: SPIDriverA() :
    SPI(SPI2, ClockControl::SPI2CLK){};};

template <> class SPIDriverA<SPI_CH3>  : public SPI {public: SPIDriverA() :
    SPI(SPI3, ClockControl::SPI3CLK){};};

} // namespace Embedded
} // namespace Micro
} // namespace STM32


#endif /* EMBEDDED_MICRO_STM32_SPI_H_ */
