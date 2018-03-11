#ifndef EMBEDDED_MICRO_STM32_CRITICALSECTION_H_
#define EMBEDDED_MICRO_STM32_CRITICALSECTION_H_

#include "libst_config.h"

namespace Embedded {
namespace Micro {
namespace STM32 {
/**
 * Represents a RAII object for creating a critical section.
 */
class CriticalSection
{
    public:
        /**
         * Upon construction, interrupts will be disabled atomically
         */
        CriticalSection();

        /**
         * Upon destruction, interrupts will be enabled atomically
         */
        virtual ~CriticalSection();

    private:
        //No private members
};

} // namespace STM32
} // namespace Micro
} // namespace Embedded







#endif /* EMBEDDED_MICRO_STM32_CRITICALSECTION_H_ */
