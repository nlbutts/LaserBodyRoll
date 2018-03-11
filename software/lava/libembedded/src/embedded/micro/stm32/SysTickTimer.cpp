#include <stdint.h>
#include <stddef.h>

#include "libst_config.h"

#include "embedded/micro/stm32/Interrupt.h"
using Embedded::Micro::STM32::Interrupt;

#include "embedded/micro/stm32/SysTickTimer.h"
using Embedded::Micro::STM32::SysTickTimer;

static bool startSystickTimer(uint32_t ticks);

SysTickTimer::SysTickTimer(uint32_t ticks) :
        Interrupt(SysTick_IRQn, Interrupt::PREEMPT_PRIO_0, Interrupt::SUB_PRIO_6),
        _ticks(ticks),
        _callback(NULL)
{
    Register(Interrupt::ISR_SysTick_Handler, this);
}

SysTickTimer::~SysTickTimer()
{
    stop();
    Unregister(Interrupt::ISR_SysTick_Handler);
}

bool SysTickTimer::start(TickCallback tickCallback)
{
    if(tickCallback == NULL)
    {
        return false;
    }

    _callback = tickCallback;

    return startSystickTimer(_ticks);
}


void SysTickTimer::stop()
{
    // Stop the timer
    SysTick->CTRL = 0x00;
}

void SysTickTimer::ISR(void)
{
    if(_callback)
    {
        _callback();
    }
}


/**
 * Modified version of the core_cm4.h SysTick_Config() function. Unlike SysTick_Config(), this
 * function uses the external clock instead of the internal clock. On the STM32F4, the external
 * clock is just the internal clock divided by 8.
 *
 * @param ticks Number of ticks between interrupts. This value will be divided by 8
 * @return true on success, else false
 */
static bool startSystickTimer(uint32_t ticks)
{
    ticks = ticks >> 3; // Divide by 8
    if (ticks > SysTick_LOAD_RELOAD_Msk)
    {
        return false;
    }

    SysTick->LOAD  = (ticks & SysTick_LOAD_RELOAD_Msk) - 1;      /* set reload register */
    //NVIC_SetPriority (SysTick_IRQn, (1<<__NVIC_PRIO_BITS) - 1);  /* set Priority for Cortex-M0 System Interrupts */
    SysTick->VAL   = 0;                                          /* Load the SysTick Counter Value */
    SysTick->CTRL  = SysTick_CTRL_TICKINT_Msk   |
                     SysTick_CTRL_ENABLE_Msk;                    /* Enable SysTick IRQ and SysTick Timer */
    return true;
}

