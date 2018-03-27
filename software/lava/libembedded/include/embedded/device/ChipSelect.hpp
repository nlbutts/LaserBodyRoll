#ifndef EMBEDDED_DEVICE_CHIP_SELECT_HPP
#define EMBEDDED_DEVICE_CHIP_SELECT_HPP

namespace Embedded {
namespace Device {


template<bool activeLow>
inline ChipSelect<activeLow>::ChipSelect(
        Embedded::Micro::Interface::IGPIO & chipSelect) :
    _chipSelect(&chipSelect),
    _holdTimer(NULL),
    _assertHoldTime_us(0),
    _deassertHoldTime_us(0)
{
    set();
}


template<bool activeLow>
inline ChipSelect<activeLow>::ChipSelect(
        Embedded::Micro::Interface::IGPIO & chipSelect,
        Embedded::Micro::Interface::ITimer & holdTimer,
        uint32_t assertHoldTime_us) :
    _chipSelect(&chipSelect),
    _holdTimer(&holdTimer),
    _assertHoldTime_us(assertHoldTime_us),
    _deassertHoldTime_us(0)
{
    set();
    _holdTimer->setTimerUs(_assertHoldTime_us);
    while(!_holdTimer->isTimerExpired());
}


template<bool activeLow>
inline ChipSelect<activeLow>::ChipSelect(
        Embedded::Micro::Interface::IGPIO & chipSelect,
        Embedded::Micro::Interface::ITimer & holdTimer,
        uint32_t assertHoldTime_us, uint32_t deassertHoldTime_us) :
    _chipSelect(&chipSelect),
    _holdTimer(&holdTimer),
    _assertHoldTime_us(assertHoldTime_us),
    _deassertHoldTime_us(deassertHoldTime_us)
{
    set();
    _holdTimer->setTimerUs(_assertHoldTime_us);
    while(!_holdTimer->isTimerExpired());
}


template<bool activeLow>
inline ChipSelect<activeLow>::~ChipSelect(void)
{
    if((_holdTimer != NULL) && (_deassertHoldTime_us != 0))
    {
        _holdTimer->setTimerUs(_deassertHoldTime_us);
        while(!_holdTimer->isTimerExpired());
    }

    clear();
    _holdTimer = NULL;
}


template<>
inline void ChipSelect<true>::set()
{
    _chipSelect->clear();
}


template<>
inline void ChipSelect<false>::set()
{
    _chipSelect->set();
}


template<>
inline void ChipSelect<true>::clear()
{
    _chipSelect->set();
}


template<>
inline void ChipSelect<false>::clear()
{
    _chipSelect->clear();
}


} // namespace Device
} // namespace Embedded

#endif /* EMBEDDED_DEVICE_CHIP_SELECT_HPP */