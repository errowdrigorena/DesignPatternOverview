#include <ObserverPattern/ConsoleObserver.hpp>

#include <iostream>
#include <utility>

namespace observer_pattern {

ConsoleObserver::ConsoleObserver(std::string name)
    : name_{std::move(name)}
{
}

void ConsoleObserver::update(const Event_enum event)
{
    std::cout << name_ << " got message " << event << '\n';
}

}  // namespace observer_pattern
