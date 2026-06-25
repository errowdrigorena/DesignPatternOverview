#pragma once
#include "StateEngine.hpp"
#include "ICoffeeMachineState.hpp"
#include "CoffeeMachineData.hpp"

namespace cg {

class CoffeeMachine
    : public StateEngine<ICoffeeMachineState<CoffeeMachine>, CoffeeMachineData>
{
public:
    CoffeeMachine();

    void selectCoffee(coffee::CoffeeOrder o)  { _state->onSelectCoffee(*this, o); }
    void grindDone()                          { _state->onGrindDone(*this); }
    void brewDone()                           { _state->onBrewDone(*this); }
    void dispenseDone()                       { _state->onDispenseDone(*this); }
    void cancel()                             { _state->onCancel(*this); }
    void fault(std::string_view r)            { _state->onFault(*this, r); }
    void reset()                              { _state->onReset(*this); }
};

} // namespace cg
