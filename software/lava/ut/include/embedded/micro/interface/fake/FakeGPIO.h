#ifndef FAKE_GPIO_H
#define FAKE_GPIO_H

#include <embedded/micro/interface/IGPIO.h>

namespace Embedded {
namespace Micro {
namespace Interface {
namespace Fake {

class FakeGPIO : public Embedded::Micro::Interface::IGPIO
{
public:
    FakeGPIO() :
        _state(&this->_innerState), _invert(false), _innerState(false), _constState(false)
    {}

    FakeGPIO(bool* state) :
        _state(state), _invert(false), _innerState(false), _constState(false)
    {}

    FakeGPIO(bool state, bool constState) :
        _state(&this->_innerState), _invert(false), _innerState(state), _constState(constState)
    {}

    virtual ~FakeGPIO()
    {}

    virtual void set()
    {
        if(!_constState)
        {
            *_state = true;
        }
    }

    virtual void clear()
    {
        if(!_constState)
        {
            *_state = false;
        }
    }

    virtual void toggle()
    {
        get() ? clear() : set();
    }

    virtual bool get() const
    {
        if(_invert)
        {
            return !(*_state);
        }
        else
        {
            return *_state;
        }
    }

    virtual void operator = (const uint32_t in)
    {
        if (in)
            set();
        else
            clear();
    }

private:
    bool* _state;
    bool _invert;

    bool _innerState;
    bool _constState;
};


} // namespace Fake
} // namespace Interface
} // namespace Micro
} // namespace Embedded

#endif /* FAKE_GPIO_H */
