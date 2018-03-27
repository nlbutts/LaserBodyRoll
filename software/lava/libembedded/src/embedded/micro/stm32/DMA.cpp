/*
 * DMADriver.cpp
 *
 *  Created on: Sep 28, 2012
 *      Author: nbutts
 */

#include <embedded/micro/stm32/DMA.h>
#include <embedded/micro/stm32/ClockControl.h>
#include <embedded/micro/stm32/Interrupt.h>
#include <cstdio>

using Embedded::Micro::STM32::DMADriver;
using Embedded::Micro::STM32::ClockControl;
using Embedded::Micro::STM32::Interrupt;

/*lint -esym(551, dma2_int_called) */
static uint32_t dma2_int_called = 0;

typedef struct
{
    IRQn_Type irq;
    Interrupt::ISR_ROUTINE isr;
    uint32_t tcClearFlag;
    DMA_Stream_TypeDef * streamBasePtr;
} DMA_MAP;

static const DMA_MAP DmaMap[] =
{
    {DMA1_Stream0_IRQn, Interrupt::ISR_DMA1_STREAM0_IRQHANDLER, DMA_IT_TCIF0 | DMA_IT_TEIF0, DMA1_Stream0},
    {DMA1_Stream1_IRQn, Interrupt::ISR_DMA1_STREAM1_IRQHANDLER, DMA_IT_TCIF1 | DMA_IT_TEIF1, DMA1_Stream1},
    {DMA1_Stream2_IRQn, Interrupt::ISR_DMA1_STREAM2_IRQHANDLER, DMA_IT_TCIF2 | DMA_IT_TEIF2, DMA1_Stream2},
    {DMA1_Stream3_IRQn, Interrupt::ISR_DMA1_STREAM3_IRQHANDLER, DMA_IT_TCIF3 | DMA_IT_TEIF3, DMA1_Stream3},
    {DMA1_Stream4_IRQn, Interrupt::ISR_DMA1_STREAM4_IRQHANDLER, DMA_IT_TCIF4 | DMA_IT_TEIF4, DMA1_Stream4},
    {DMA1_Stream5_IRQn, Interrupt::ISR_DMA1_STREAM5_IRQHANDLER, DMA_IT_TCIF5 | DMA_IT_TEIF5, DMA1_Stream5},
    {DMA1_Stream6_IRQn, Interrupt::ISR_DMA1_STREAM6_IRQHANDLER, DMA_IT_TCIF6 | DMA_IT_TEIF6, DMA1_Stream6},
    {DMA1_Stream7_IRQn, Interrupt::ISR_DMA1_STREAM7_IRQHANDLER, DMA_IT_TCIF7 | DMA_IT_TEIF7, DMA1_Stream7},

    {DMA2_Stream0_IRQn, Interrupt::ISR_DMA2_STREAM0_IRQHANDLER, DMA_IT_TCIF0 | DMA_IT_TEIF0, DMA2_Stream0},
    {DMA2_Stream1_IRQn, Interrupt::ISR_DMA2_STREAM1_IRQHANDLER, DMA_IT_TCIF1 | DMA_IT_TEIF1, DMA2_Stream1},
    {DMA2_Stream2_IRQn, Interrupt::ISR_DMA2_STREAM2_IRQHANDLER, DMA_IT_TCIF2 | DMA_IT_TEIF2, DMA2_Stream2},
    {DMA2_Stream3_IRQn, Interrupt::ISR_DMA2_STREAM3_IRQHANDLER, DMA_IT_TCIF3 | DMA_IT_TEIF3, DMA2_Stream3},
    {DMA2_Stream4_IRQn, Interrupt::ISR_DMA2_STREAM4_IRQHANDLER, DMA_IT_TCIF4 | DMA_IT_TEIF4, DMA2_Stream4},
    {DMA2_Stream5_IRQn, Interrupt::ISR_DMA2_STREAM5_IRQHANDLER, DMA_IT_TCIF5 | DMA_IT_TEIF5, DMA2_Stream5},
    {DMA2_Stream6_IRQn, Interrupt::ISR_DMA2_STREAM6_IRQHANDLER, DMA_IT_TCIF6 | DMA_IT_TEIF6, DMA2_Stream6},
    {DMA2_Stream7_IRQn, Interrupt::ISR_DMA2_STREAM7_IRQHANDLER, DMA_IT_TCIF7 | DMA_IT_TEIF7, DMA2_Stream7},
};

DMADriver::DMADriver(uint32_t * src, uint32_t * dst, uint16_t size)
: Interrupt(DmaMap[static_cast<uint32_t>(DMADriver::DMA2_ST0)].irq)
, _stream(DMADriver::DMA2_ST0)
, _channel(DMADriver::CH0)
, _transferComplete(false)
, TIMEOUT_MAX(10000)
{
    Interrupt::Register(DmaMap[static_cast<IRQn_Type>(_stream)].isr, this);

    enableDMAClock();
    getDmaStreamRegPtr();
    (void)stop();

    /* Configure DMA Stream */
    _dmaConfig.DMA_Channel = getChannelMask(DMADriver::CH0);
    _dmaConfig.DMA_PeripheralBaseAddr = (uint32_t)src;
    _dmaConfig.DMA_Memory0BaseAddr = (uint32_t)dst;
    _dmaConfig.DMA_DIR = DMA_DIR_MemoryToMemory;
    _dmaConfig.DMA_BufferSize = size;
    _dmaConfig.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    _dmaConfig.DMA_MemoryInc = DMA_MemoryInc_Enable;
    _dmaConfig.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
    _dmaConfig.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;
    _dmaConfig.DMA_Mode = DMA_Mode_Normal;
    _dmaConfig.DMA_Priority = DMA_Priority_High;
    _dmaConfig.DMA_FIFOMode = DMA_FIFOMode_Disable;
    _dmaConfig.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
    _dmaConfig.DMA_MemoryBurst = DMA_MemoryBurst_Single;
    _dmaConfig.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
    DMA_Init(_dmaStreamRegs, &_dmaConfig);

    /* Enable DMA Stream Transfer Complete interrupt */
    DMA_ITConfig(_dmaStreamRegs, DMA_IT_TC, ENABLE);
}

DMADriver::DMADriver(DMA_STREAM stream, DMA_CHANNEL ch)
: Interrupt(DmaMap[static_cast<uint32_t>(stream)].irq)
, _stream(stream)
, _channel(ch)
, _transferComplete(false)
, TIMEOUT_MAX(10000)
{
    Interrupt::Register(DmaMap[static_cast<IRQn_Type>(_stream)].isr, this);

    enableDMAClock();
    getDmaStreamRegPtr();
    (void)stop();

    /* Configure DMA Stream */
    _dmaConfig.DMA_Channel = getChannelMask(_channel);
    _dmaConfig.DMA_PeripheralBaseAddr = 0;
    _dmaConfig.DMA_Memory0BaseAddr = 0;
    _dmaConfig.DMA_BufferSize = 0;
    _dmaConfig.DMA_DIR = DMA_DIR_MemoryToPeripheral;
    _dmaConfig.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    _dmaConfig.DMA_MemoryInc = DMA_MemoryInc_Enable;
    _dmaConfig.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    _dmaConfig.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    _dmaConfig.DMA_Mode = DMA_Mode_Normal;
    _dmaConfig.DMA_Priority = DMA_Priority_High;
    _dmaConfig.DMA_FIFOMode = DMA_FIFOMode_Disable;
    _dmaConfig.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
    _dmaConfig.DMA_MemoryBurst = DMA_MemoryBurst_Single;
    _dmaConfig.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
    DMA_Init(_dmaStreamRegs, &_dmaConfig);

    /* Enable DMA Stream Transfer Complete interrupt */
    DMA_ITConfig(_dmaStreamRegs, DMA_IT_TC, ENABLE);
}

DMADriver::~DMADriver()
{
    DMA_ITConfig(_dmaStreamRegs, DMA_IT_TC, DISABLE);
    Interrupt::Unregister(DmaMap[static_cast<IRQn_Type>(_stream)].isr);
    _dmaModule = NULL;
    _dmaStreamRegs = NULL;
}

bool DMADriver::stop()
{
    uint32_t Timeout = TIMEOUT_MAX;
    bool success = true;

    /* Reset DMA Stream registers (for debug purpose) */
    DMA_DeInit(_dmaStreamRegs);

    /* Check if the DMA Stream is disabled before enabling it.
       Note that this step is useful when the same Stream is used multiple times:
       enabled, then disabled then re-enabled... In this case, the DMA Stream disable
       will be effective only at the end of the ongoing data transfer and it will
       not be possible to re-configure it before making sure that the Enable bit
       has been cleared by hardware. If the Stream is used only once, this step might
       be bypassed. */
    while ((DMA_GetCmdStatus(_dmaStreamRegs) != DISABLE) && (--Timeout > 0))
    {
    }

    if (Timeout == 0)
    {
        success = false;
    }
    return success;
}

bool DMADriver::start()
{
    bool successfullyStarted = true;
    _transferComplete = false;

    /* DMA Stream enable */
    clearPendingInterrupt();
    DMA_Cmd(_dmaStreamRegs, ENABLE);

    /* Check if the DMA Stream has been effectively enabled.
       The DMA Stream Enable bit is cleared immediately by hardware if there is an
       error in the configuration parameters and the transfer is no started (ie. when
       wrong FIFO threshold is configured ...) */
    uint32_t Timeout = TIMEOUT_MAX;
    while ((--Timeout > 0) && (DMA_GetCmdStatus(_dmaStreamRegs) != ENABLE))
    {
    }

    /* Check if a timeout condition occurred */
    if (Timeout == 0)
    {
        successfullyStarted = false;
    }
    return successfullyStarted;
}

void DMADriver::ISR(void)
{
    clearPendingInterrupt();
    _transferComplete = true;
    dma2_int_called++;
}


bool DMADriver::updatePtrs(uint32_t src, uint32_t dst, uint16_t size)
{
    if (_dmaConfig.DMA_DIR == DMA_DIR_PeripheralToMemory)
    {
        _dmaConfig.DMA_Memory0BaseAddr = dst;
        _dmaConfig.DMA_PeripheralBaseAddr = src;
        _dmaConfig.DMA_BufferSize = size;
    }
    else
    {
        _dmaConfig.DMA_Memory0BaseAddr = src;
        _dmaConfig.DMA_PeripheralBaseAddr = dst;
        _dmaConfig.DMA_BufferSize = size;
    }
    DMA_Init(_dmaStreamRegs, &_dmaConfig);
    return true;
}

void DMADriver::enableDMAClock()
{
    if (_stream <= DMA1_ST7)
    {
        ClockControl::enable(ClockControl::DMA1CLK);
        _dmaModule = DMA1;
    }
    else
    {
        ClockControl::enable(ClockControl::DMA2CLK);
        _dmaModule = DMA2;
    }
}

void DMADriver::getDmaStreamRegPtr()
{
    _dmaStreamRegs = DmaMap[static_cast<uint32_t>(_stream)].streamBasePtr;
}

void DMADriver::clearPendingInterrupt()
{
    uint32_t mask = DmaMap[static_cast<uint32_t>(_stream)].tcClearFlag;

    /* Clear DMA Stream Transfer Complete interrupt pending bit */
    DMA_ClearITPendingBit(_dmaStreamRegs, mask);
}

uint32_t DMADriver::getChannelMask(DMA_CHANNEL channel) const
{
    uint32_t mask = static_cast<uint32_t>(channel);
    // This is to convert from a channel number to a enable mask
    mask <<= 25;
    return mask;
}

void DMADriver::setMemoryToPeripheral()
{
    _dmaConfig.DMA_DIR = DMA_DIR_MemoryToPeripheral;
    DMA_Init(_dmaStreamRegs, &_dmaConfig);
}

void DMADriver::setPeripheralToMemory()
{
    _dmaConfig.DMA_DIR = DMA_DIR_PeripheralToMemory;
    _dmaConfig.DMA_MemoryInc = DMA_MemoryInc_Disable;
    DMA_Init(_dmaStreamRegs, &_dmaConfig);
}

uint16_t DMADriver::getBytesRemaining() const
{
    return static_cast<uint16_t>(_dmaStreamRegs->NDTR);
}

void DMADriver::setTransferWidth(DMA_TRANSFER_WIDTH width)
{
    switch (width)
    {
        case BYTE:
            _dmaConfig.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
            _dmaConfig.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
            break;
        case HALF_WORD:
            _dmaConfig.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
            _dmaConfig.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
            break;
        case WORD:
            _dmaConfig.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;
            _dmaConfig.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
            break;
    }
    DMA_Init(_dmaStreamRegs, &_dmaConfig);
}

void DMADriver::setBufferMode(DMA_BUFFER_MODE mode)
{
    if (mode == NORMAL)
    {
        _dmaConfig.DMA_Mode = DMA_Mode_Normal;
    }
    else
    {
        _dmaConfig.DMA_Mode = DMA_Mode_Circular;
    }
    DMA_Init(_dmaStreamRegs, &_dmaConfig);
}

void DMADriver::enableMemoryInc()
{
    _dmaConfig.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_Init(_dmaStreamRegs, &_dmaConfig);
}
