#ifndef EMBEDDED_DEVICE_CHIP_SELECT_H
#define EMBEDDED_DEVICE_CHIP_SELECT_H

#include <stdint.h>
#include <stddef.h>

#include "embedded/micro/interface/IGPIO.h"
#include "embedded/micro/interface/ITimer.h"


namespace Embedded {
namespace Device {


/**
 * @brief Class for managing the chip select line of a SPI chip
 * @details This class sets chips select to active on construction, and
 * deactivates chip select on destruction.
 *
 * @param activeLow true for active low chip select, false for active high chip
 *          select
 */
template<bool activeLow>
class ChipSelect
{
public:
    /**
     * @brief Simple constructor
     * @details Sets chip select active on construction
     *
     * @param chipSelect Chip select GPIO
     */
    ChipSelect(Embedded::Micro::Interface::IGPIO & chipSelect);


    /**
     * @brief Advanced constructor
     * @details Sets chip select active on construction. This will block
     *          for the given assertion hold time before returning
     *
     * @param chipSelect Chip select GPIO
     * @param holdTimer Timer to use when performing the dealy
     * @param assertHoldTime_us Time to block, in microseconds, after asserting
     *          the chip select line
     */
    ChipSelect(Embedded::Micro::Interface::IGPIO & chipSelect,
               Embedded::Micro::Interface::ITimer & holdTimer,
               uint32_t assertHoldTime_us);


    /**
     * @brief Really advanced constructor
     * @details Sets chip select active on construction. This will block
     *          for the given assertion hold time before returning
     *
     * @param chipSelect Chip select GPIO
     * @param holdTimer Timer to use when performing the dealy
     * @param assertHoldTime_us Time to block, in microseconds, after asserting
     *          the chip select line
     * @param deassertHoldTime_us Time to block, in microseconds, after
     *          de-asserting the chip select line
     */
    ChipSelect(Embedded::Micro::Interface::IGPIO & chipSelect,
               Embedded::Micro::Interface::ITimer & holdTimer,
               uint32_t assertHoldTime_us, uint32_t deassertHoldTime_us);


    /**
     * @brief Destructor
     * @details Sets chip select inactive on destruction. If a de-assertion
     *          time was specified, then this will block for the given
     *          de-assertion time before setting the chip select inactive
     */
    ~ChipSelect();


private:
    Embedded::Micro::Interface::IGPIO  *_chipSelect;
    Embedded::Micro::Interface::ITimer *_holdTimer;
    uint32_t                            _assertHoldTime_us;
    uint32_t                            _deassertHoldTime_us;

    inline void set(void);
    inline void clear(void);
};


} // namespace Device
} // namespace Embedded

#include "embedded/device/ChipSelect.hpp"

#endif /* EMBEDDED_DEVICE_CHIP_SELECT_H */