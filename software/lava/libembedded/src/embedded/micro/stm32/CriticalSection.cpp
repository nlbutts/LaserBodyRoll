#include "embedded/micro/stm32/CriticalSection.h"

using Embedded::Micro::STM32F4::CriticalSection;

CriticalSection::CriticalSection()
{
    __disable_irq();
}

CriticalSection::~CriticalSection()
{
    __enable_irq();
}


