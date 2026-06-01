#include <ObserverPattern_classic/Subject.hpp>

#include <algorithm>

namespace observer_pattern {

void Subject::subscribe(Observer& observer)
{
    if (std::ranges::find(observers_, &observer) == observers_.end()) {
        observers_.push_back(&observer);
    }
}

void Subject::unsubscribe(Observer& observer)
{
    std::erase(observers_, &observer);
}

void Subject::notify(const Event_enum event)
{
    const auto observers = observers_;
    for (auto* observer : observers) {
        observer->update(event);
    }
}

}  // namespace observer_pattern
