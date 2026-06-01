#pragma once

#include <ObserverPattern_common/Event.hpp>
#include <ObserverPattern_classic/Observer.hpp>

#include <string>

namespace observer_pattern {

class ConsoleObserver final : public Observer {
public:
    explicit ConsoleObserver(std::string name);

    void update(Event_enum event) override;

private:
    std::string name_;
};

}  // namespace observer_pattern
