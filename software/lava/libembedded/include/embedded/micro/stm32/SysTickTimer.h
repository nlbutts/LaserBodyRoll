#ifndef EMBEDDED_MICRO_STM32_SYSTICKTIMER_H_
#define EMBEDDED_MICRO_STM32_SYSTICKTIMER_H_

#include <stdint.h>
#include <embedded/micro/interface/ITickTimer.h>
#include <embedded/micro/stm32/Interrupt.h>

namespace Embedded {
namespace Micro {
namespace STM32 {

/**
 * @brief ARM Cortex SysTick wrapper
 */
class SysTickTimer : public Embedded::Micro::Interface::ITickTimer,
                      public Embedded::Micro::STM32::Interrupt
{
public:
    typedef void (*TickCallback)(void);

public:
    /**
     * Constructor
     *
     * @param dev SysTick device
     * @param ticks Number of CPU ticks between each interrupt
     */
    SysTickTimer(uint32_t ticks);

    /**
     * Destructor
     */
    virtual ~SysTickTimer();

    /**
     * Inherited from ITickTimer.
     *
     * Configures and starts the timer which will call the provided callback each tick.
     *
     * @param tickCallback Pointer to a function that will be called each timer tick.
     * @return true if configured and started or false
     */
    bool start(TickCallback tickCallback);

    /**
     * Inherited from ITickTimer.
     *
     * Stops the the timer.
     */
    void stop();

    /**
     * Inherited from Interrupt
     *
     * SysTick ISR function
     */
    void ISR(void);

private:
    uint32_t        _ticks;
    TickCallback    _callback;
};


} // namespace STM32
} // namespace Micro
} // namespace Embedded

#endif /* EMBEDDED_MICRO_STM32_SYSTICKTIMER_H_ */
