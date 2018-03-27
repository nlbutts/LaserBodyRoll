#ifndef EMBEDDED_MICRO_STM32_DMA_H_
#define EMBEDDED_MICRO_STM32_DMA_H_

#include "libst_config.h"
#include <embedded/micro/stm32/Interrupt.h>

namespace Embedded {
namespace Micro {
namespace STM32 {

class DMADriver : public Interrupt
{
    public:
        typedef enum
        {
            DMA1_ST0,
            DMA1_ST1,
            DMA1_ST2,
            DMA1_ST3,
            DMA1_ST4,
            DMA1_ST5,
            DMA1_ST6,
            DMA1_ST7,

            DMA2_ST0,
            DMA2_ST1,
            DMA2_ST2,
            DMA2_ST3,
            DMA2_ST4,
            DMA2_ST5,
            DMA2_ST6,
            DMA2_ST7,
        } DMA_STREAM;

        typedef enum
        {
            CH0,
            CH1,
            CH2,
            CH3,
            CH4,
            CH5,
            CH6,
            CH7,
        } DMA_CHANNEL;

        typedef enum
        {
            BYTE,
            HALF_WORD,
            WORD,
        } DMA_TRANSFER_WIDTH;

        typedef enum
        {
            NORMAL,
            CIRCULAR,
        } DMA_BUFFER_MODE;

        typedef enum
        {
            SPI1TX,
            SPI1RX,
            SPI2TX,
            SPI2RX,
            USART1TX,
            USART1RX,
            USART2TX,
            USART2RX,
            USART3TX,
            USART3RX,
            USART6TX,
            USART6RX,
            SDIODMA,
            ADC1DMA,
            ADC3DMA,
            SPI2_I2S2_RX,
            SPI3_I2S3_RX
        } DMA_MAPPING;

        /**
         * This is the memory to memory DMA constuctor, only one instances should exist
         *
         * @param src the pointer to the source buffer
         * @param dst the pointer to the destination location.
         * @param size the amount of data to transfer
         */
        DMADriver(uint32_t * src, uint32_t * dst, uint16_t size);
        /**
         * This is a used to setup a DMA transfer between memory and a peripherial
         *
         * @param stream the stream to setup
         * @param ch the channel to setup
         */
        DMADriver(DMA_STREAM stream, DMA_CHANNEL ch);
        virtual ~DMADriver();
        /**
         * Stops a DMA transfer in progress
         *
         * @bool true if successfully stopped or false if unsuccessful.
         */
        bool stop();
        /**
         * Starts a DMA transfer
         *
         * @bool true if successfully started or false if unsuccessful.
         */
        bool start();
        /**
         * The DMA class inherits from the Interrupt class. When a end of DMA completes
         * this function gets called.
         *
         */
        void ISR();
        /**
         * Updates the pointers in the DMA engine, the DMA will always transfer data
         * from the src pointer to the dst pointer. It is up to the user to setup the
         * pointers prior to a transfer
         *
         * @param src the source pointer, either memory or a peripherial address
         * @param dst the destination pointer, either memory or a peripherial address
         * @param size the size in bytes of the transfer, there is an upper limit of 65535
         * @bool true if successfully started or false if unsuccessful.
         */
        bool updatePtrs(uint32_t src, uint32_t dst, uint16_t size);
        /**
         * This function indicates if a transfer is in progress, or if the transfer
         * has completed.
         *
         * @bool true if the transfer is complete
         */
        inline bool isTransferComplete()   {return _transferComplete;}
        /**
         * Clears a pending DMA interrupt
         */
        void clearPendingInterrupt();
        /**
         * Sets the DMA to be a memory to peripheral transfer
         */
        void setMemoryToPeripheral();
        /**
         * Sets the DMA to be a peripheral to memory transfer
         */
        void setPeripheralToMemory();
        /**
         * Gets the bytes remaining in the transfer
         */
        uint16_t getBytesRemaining() const;
        /**
         * Sets the DMA transfer width, either a full word (32-bits), half-word (16-bits)
         * or a byte transfer
         *
         * @param width the transfer width
         */
        void setTransferWidth(DMA_TRANSFER_WIDTH width);
        /**
         * This function indicates if a transfer is in progress, or if the transfer
         * has completed.
         *
         * @bool true if the transfer is complete
         */
        void setBufferMode(DMA_BUFFER_MODE mode);

        /**
         * Enables the memory to be incremented after each transfer
         *
         */
        void enableMemoryInc();

    private:
        DMA_STREAM _stream;
        DMA_CHANNEL _channel;
        DMA_TypeDef *_dmaModule;
        DMA_InitTypeDef _dmaConfig;
        DMA_Stream_TypeDef * _dmaStreamRegs;
        volatile bool _transferComplete;

        const uint32_t TIMEOUT_MAX;

        void enableDMAClock();
        void getDmaStreamRegPtr();
        uint32_t getChannelMask(DMA_CHANNEL channel) const;
};

template <DMADriver::DMA_MAPPING T> class DMADriverA;

template <> class DMADriverA<DMADriver::SPI1TX>       : public DMADriver {public: DMADriverA() : DMADriver(DMADriver::DMA2_ST5, DMADriver::CH3){};};
template <> class DMADriverA<DMADriver::SPI1RX>       : public DMADriver {public: DMADriverA() : DMADriver(DMADriver::DMA2_ST2, DMADriver::CH3){};};
template <> class DMADriverA<DMADriver::SPI2TX>       : public DMADriver {public: DMADriverA() : DMADriver(DMADriver::DMA1_ST4, DMADriver::CH0){};};
template <> class DMADriverA<DMADriver::SPI2RX>       : public DMADriver {public: DMADriverA() : DMADriver(DMADriver::DMA1_ST3, DMADriver::CH0){};};
template <> class DMADriverA<DMADriver::USART1TX>     : public DMADriver {public: DMADriverA() : DMADriver(DMADriver::DMA2_ST7, DMADriver::CH4){};};
template <> class DMADriverA<DMADriver::USART1RX>     : public DMADriver {public: DMADriverA() : DMADriver(DMADriver::DMA2_ST5, DMADriver::CH4){};};
template <> class DMADriverA<DMADriver::USART2TX>     : public DMADriver {public: DMADriverA() : DMADriver(DMADriver::DMA1_ST6, DMADriver::CH4){};};
template <> class DMADriverA<DMADriver::USART2RX>     : public DMADriver {public: DMADriverA() : DMADriver(DMADriver::DMA1_ST5, DMADriver::CH4){};};
template <> class DMADriverA<DMADriver::USART3TX>     : public DMADriver {public: DMADriverA() : DMADriver(DMADriver::DMA1_ST3, DMADriver::CH4){};};
template <> class DMADriverA<DMADriver::USART3RX>     : public DMADriver {public: DMADriverA() : DMADriver(DMADriver::DMA1_ST1, DMADriver::CH4){};};
template <> class DMADriverA<DMADriver::USART6TX>     : public DMADriver {public: DMADriverA() : DMADriver(DMADriver::DMA2_ST6, DMADriver::CH5){};};
template <> class DMADriverA<DMADriver::USART6RX>     : public DMADriver {public: DMADriverA() : DMADriver(DMADriver::DMA2_ST1, DMADriver::CH5){};};
template <> class DMADriverA<DMADriver::SDIODMA>      : public DMADriver {public: DMADriverA() : DMADriver(DMADriver::DMA2_ST3, DMADriver::CH4){};};
template <> class DMADriverA<DMADriver::ADC1DMA>      : public DMADriver {public: DMADriverA() : DMADriver(DMADriver::DMA2_ST0, DMADriver::CH0){};};
template <> class DMADriverA<DMADriver::ADC3DMA>      : public DMADriver {public: DMADriverA() : DMADriver(DMADriver::DMA2_ST0, DMADriver::CH2){};};
template <> class DMADriverA<DMADriver::SPI2_I2S2_RX> : public DMADriver {public: DMADriverA() : DMADriver(DMADriver::DMA1_ST3, DMADriver::CH0){};};
template <> class DMADriverA<DMADriver::SPI3_I2S3_RX> : public DMADriver {public: DMADriverA() : DMADriver(DMADriver::DMA1_ST0, DMADriver::CH0){};};

} // namespace Embedded
} // namespace Micro
} // namespace STM32

#endif /* EMBEDDED_MICRO_STM32_DMA_H_ */
