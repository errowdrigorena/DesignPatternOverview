#pragma once

#include <ObserverPattern/Event.hpp>

namespace observer_pattern {

class Observer {
public:
    virtual ~Observer() = default;

    virtual void update(Event_enum event) = 0;
};

}  // namespace observer_pattern
