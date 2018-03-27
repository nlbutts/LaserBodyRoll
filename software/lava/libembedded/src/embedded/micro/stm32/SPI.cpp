#include <stddef.h>

#include <embedded/micro/stm32/SPI.h>

namespace Embedded {
namespace Micro {
namespace STM32 {

SPI::SPI(SPI_TypeDef * spiBase)
: _dev(spiBase)
, _txDMA(NULL)
, _rxDMA(NULL)
{
    setupInputClock();
    //SPI_StructInit(&_spiCfg);
}

SPI::SPI(SPI_TypeDef * spiBase, DMADriver &txDMA, DMADriver &rxDMA)
: _dev(spiBase)
, _txDMA(&txDMA)
, _rxDMA(&rxDMA)
{
    setupInputClock();
    //SPI_StructInit(&_spiCfg);

    _txDMA->setMemoryToPeripheral();
    _rxDMA->setPeripheralToMemory();
}

SPI::~SPI()
{
    _rxDMA  = NULL;
    _txDMA  = NULL;
    _dev    = NULL;
}

void SPI::setupSPI(bool master, bool size8b, bool CPOLhigh, bool CPHAedge1, bool msbFirst)
{
    /*!< SPI configuration */
    _spiCfg.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    if (master)
    {
        _spiCfg.SPI_Mode = SPI_Mode_Master;
    }
    else
    {
        _spiCfg.SPI_Mode = SPI_Mode_Slave;
    }
    if (size8b)
    {
        _spiCfg.SPI_DataSize = SPI_DataSize_8b;
    }
    else
    {
        _spiCfg.SPI_DataSize = SPI_DataSize_16b;
    }
    if (CPOLhigh)
    {
        _spiCfg.SPI_CPOL = SPI_CPOL_High;
    }
    else
    {
        _spiCfg.SPI_CPOL = SPI_CPOL_Low;
    }
    if (CPHAedge1)
    {
        _spiCfg.SPI_CPHA = SPI_CPHA_1Edge;
    }
    else
    {
        _spiCfg.SPI_CPHA = SPI_CPHA_2Edge;
    }
    _spiCfg.SPI_NSS = SPI_NSS_Soft;

    if (msbFirst)
    {
        _spiCfg.SPI_FirstBit = SPI_FirstBit_MSB;
    }
    else
    {
        _spiCfg.SPI_FirstBit = SPI_FirstBit_LSB;
    }
    _spiCfg.SPI_CRCPolynomial = 7;

    SPI_Init(_dev, &_spiCfg);
    SPI_Cmd(_dev, ENABLE);
}

uint32_t SPI::setFrequency(uint32_t frequency)
{
    uint16_t baudPrescaler;
    uint32_t actualFrequency;
    for (baudPrescaler = 0; baudPrescaler < 7; ++baudPrescaler)
    {
        if (_fpclk / (1U << (baudPrescaler + 1)) <= frequency)
        {
            break;
        }
    }

    _spiCfg.SPI_BaudRatePrescaler = baudPrescaler << 3; //lint !e734 : baudPrescaler can't lose any bits

    // Calculate the new baud rate
    actualFrequency = _fpclk / (2 << baudPrescaler);
    SPI_Init(_dev, &_spiCfg);
    SPI_Cmd(_dev, ENABLE);
    return actualFrequency;
}

void SPI::setDivider(SPI_BR divider)
{
    _spiCfg.SPI_BaudRatePrescaler = static_cast<uint16_t>(divider);
    SPI_Init(_dev, &_spiCfg);
    SPI_Cmd(_dev, ENABLE);
}

void SPI::read(uint8_t * rx, uint16_t len)
{
    while (_dev->SR & SPI_I2S_FLAG_BSY){};

    // Make sure there are no left over bytes from the previous transaction
    emptyRxQueue();

    for (int i = 0; i < len; ++i)
    {
        _dev->DR = 0;
        while (!(_dev->SR & SPI_I2S_FLAG_RXNE)){};
        *(rx + i) = static_cast<uint8_t>(_dev->DR);
    }
}


uint16_t SPI::write(const uint8_t * tx, uint16_t len)
{
    while (!(_dev->SR & SPI_I2S_FLAG_TXE)){};

    emptyRxQueue();

    for (int i = 0; i < len; ++i)
    {
        _dev->DR = *(tx + i);
        while (!(_dev->SR & SPI_I2S_FLAG_RXNE)){};
        (void) static_cast<uint8_t>(_dev->DR);
    }

    while (_dev->SR & SPI_I2S_FLAG_BSY) {};

    return len;
}


uint16_t SPI::write(const uint8_t * tx, uint8_t * rx, uint16_t len)
{
    if(tx == NULL)
    {
        return 0;
    }

    while (!(_dev->SR & SPI_I2S_FLAG_TXE)){};

    for (int i = 0; i < len; ++i)
    {
        _dev->DR = *(tx + i);
        while (!(_dev->SR & SPI_I2S_FLAG_RXNE)){};
        uint8_t reg = static_cast<uint8_t>(_dev->DR);
        if (rx)
        {
            *(rx + i) = reg;
        }
    }

    while (_dev->SR & SPI_I2S_FLAG_BSY) {};

    return len;
}

void SPI::flushDMA()
{
    if(_txDMA != NULL)
    {
        while (_txDMA->getBytesRemaining() > 0){};
    }
}   //lint !e1762 : not logically const


bool SPI::isDMAInProgress()
{
    bool txFinished = false;
    if(_txDMA != NULL)
    {
        txFinished = (_txDMA->getBytesRemaining() > 0 ? true : false);
    }

    bool rxFinished = false;
    if(_rxDMA != NULL)
    {
        rxFinished = (_rxDMA->getBytesRemaining() > 0 ? true : false);
    }

    return txFinished && rxFinished;
}


bool SPI::writeDMA(const uint8_t * tx, uint8_t * rx, uint16_t len)
{
    /*
     * This will block until the DMA has completed the transfer. It is best if the callee
     * makes this decision and delays writting data to the DMA.
     */
    if(_txDMA == NULL)
    {
        return false;
    }

    flushDMA();
    if (rx != NULL)
    {
        _rxDMA->updatePtrs((uint32_t)&_dev->DR, (uint32_t)rx, len); //lint !e534 : ignore return
        SPI_I2S_DMACmd(_dev, SPI_I2S_DMAReq_Rx, ENABLE);
        _rxDMA->start();                                            //lint !e534 : ignore return
    }
    _txDMA->updatePtrs((uint32_t)tx, (uint32_t)&_dev->DR, len);     //lint !e534 : ignore return
    SPI_I2S_DMACmd(_dev, SPI_I2S_DMAReq_Tx, ENABLE);
    _txDMA->start();                                                //lint !e534 : ignore return
    return true;
}

void SPI::setupInputClock()
{
    if (_dev == SPI1)
    {
        _fpclk = SystemCoreClock / 2;
    }
    else
    {
        _fpclk = SystemCoreClock / 4;
    }
}

void SPI::emptyRxQueue(void)
{
    while (_dev->SR & SPI_I2S_FLAG_RXNE)
    {
        (void) static_cast<uint8_t>(_dev->DR);
    }
}

} // namespace STM32
} // namespace Micro
} // namespace Embedded

