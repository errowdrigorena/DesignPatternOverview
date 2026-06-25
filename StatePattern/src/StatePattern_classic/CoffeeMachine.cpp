#include "StatePattern_classic/CoffeeMachine.hpp"
#include "StatePattern_classic/States.hpp"
#include <stdexcept>

CoffeeMachine::CoffeeMachine()
    : _state(std::make_unique<ReadyState>())
{}

void CoffeeMachine::selectCoffee(coffee::CoffeeOrder order) { _state->onSelectCoffee(*this, order); }
void CoffeeMachine::grindDone()                             { _state->onGrindDone(*this); }
void CoffeeMachine::brewDone()                              { _state->onBrewDone(*this); }
void CoffeeMachine::dispenseDone()                          { _state->onDispenseDone(*this); }
void CoffeeMachine::cancel()                                { _state->onCancel(*this); }
void CoffeeMachine::fault(std::string_view reason)          { _state->onFault(*this, reason); }
void CoffeeMachine::reset()                                 { _state->onReset(*this); }

std::string_view CoffeeMachine::stateName() const { return _state->name(); }

bool CoffeeMachine::hasOrder() const { return _order.has_value(); }

const coffee::CoffeeOrder& CoffeeMachine::currentOrder() const {
    if (!_order) throw std::logic_error("No active order");
    return *_order;
}

const coffee::CoffeeProfile& CoffeeMachine::currentProfile() const {
    if (!_profile) throw std::logic_error("No active profile");
    return *_profile;
}

const std::string& CoffeeMachine::faultReason() const { return _faultReason; }

void CoffeeMachine::transitionTo(std::unique_ptr<ICoffeeMachineState> next) {
    _state = std::move(next);
}

void CoffeeMachine::setupOrder(coffee::CoffeeOrder order) {
    _order   = order;
    _profile = coffee::profileFor(order);
}

void CoffeeMachine::clearOrder() {
    _order.reset();
    _profile.reset();
    _faultReason.clear();
}

void CoffeeMachine::recordFault(std::string reason) {
    _faultReason = std::move(reason);
}
