#ifndef EMBEDDED_MICRO_INTERFACE_ITIMER_H_
#define EMBEDDED_MICRO_INTERFACE_ITIMER_H_

#include <stdint.h>

namespace Embedded {
namespace Micro {
namespace Interface {

/**
 * Specifies the contract of a TimerDriver
 *
 */
class ITimer
{
public:
    /**
     * Destroys an instance of <code>ITimer</code>.
     */
    virtual ~ITimer() {};

    /**
     * This function sets a expiration timer
     *
     * @param timeoutInMs time in milliseconds
     */
    virtual void setTimerMs(uint32_t timeoutInMs) = 0;
    virtual void setTimerUs(uint32_t timeoutInUs) = 0;

    /**
     * This function returns true if this timer has expired
     *
     * @return bool true if the timer has expired, false otherwise
     */
    virtual bool isTimerExpired() const = 0;

protected:
    /**
     * Protected to comply with pure virtual interface.
     */
    ITimer() {};
};

} // namespace Interface
} // namespace Micro
} // namespace Embedded

#endif /* EMBEDDED_MICRO_INTERFACE_ITIMER_H_ */
