#include <ObserverPattern/Subject.hpp>

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
    for (auto* observer : observers_) {
        observer->update(event);
    }
}

}  // namespace observer_pattern
