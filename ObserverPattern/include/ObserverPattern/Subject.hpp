#pragma once

#include <ObserverPattern/Event.hpp>
#include <ObserverPattern/Observer.hpp>

#include <vector>

namespace observer_pattern {

class Subject {
public:
    virtual ~Subject() = default;

    void subscribe(Observer& observer);
    void unsubscribe(Observer& observer);
    void notify(Event_enum event);

private:
    std::vector<Observer*> observers_;
};

}  // namespace observer_pattern
