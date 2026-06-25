#include "StatePattern_classic_generic/CoffeeMachine.hpp"
#include "StatePattern_classic_generic/States.hpp"

namespace cg {

CoffeeMachine::CoffeeMachine()
    : StateEngine(std::make_unique<ReadyState<CoffeeMachine>>())
{}

} // namespace cg
