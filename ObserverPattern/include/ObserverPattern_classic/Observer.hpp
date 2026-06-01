#pragma once

#include <ObserverPattern_common/Event.hpp>

namespace observer_pattern {

class Observer {
public:
    virtual ~Observer() = default;

    virtual void update(Event_enum event) = 0;
};

}  // namespace observer_pattern
