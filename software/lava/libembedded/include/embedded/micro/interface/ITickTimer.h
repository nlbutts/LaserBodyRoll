#ifndef EMBEDDED_MICRO_INTERFACE_ITICKTIMER_H_
#define EMBEDDED_MICRO_INTERFACE_ITICKTIMER_H_

namespace Embedded {
namespace Micro {
namespace Interface {

/**
 * @brief Specifies the contract of a Tick timer
 * This timer interface is used for schedulers and tasks that need periodic callbacks
 */
class ITickTimer
{
public:
    /**
     * Destructor
     */
    virtual ~ITickTimer() {};

    /**
     * Configures and starts the timer which will call the provided callback each tick.
     *
     * @param tickCallback Pointer to a function that will be called each timer tick.
     * @return true if configured and started else false
     */
    virtual bool start(void (*tickCallback)(void)) = 0;

    /**
     * Stops the the timer.
     */
    virtual void stop() = 0;

protected:
    /**
     * Constructor
     */
    ITickTimer() {};
};

} // namespace Interface
} // namespace Micro
} // namespace Embedded

#endif /* EMBEDDED_MICRO_INTERFACE_ITICKTIMER_H_ */
