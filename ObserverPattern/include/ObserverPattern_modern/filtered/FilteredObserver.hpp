#pragma once

#include <ObserverPattern_common/Event.hpp>
#include <ObserverPattern_modern/signal_slot/Subject.hpp>

#include <functional>
#include <memory>
#include <string>
#include <iostream>

namespace observer_pattern_modern::filtered {

class FilteredObserver : public std::enable_shared_from_this<FilteredObserver> {
public:
    using Predicate = std::function<bool(observer_pattern::Event_enum)>;

    explicit FilteredObserver(std::string name, Predicate pred = [](auto) { return true; })
        : name_{std::move(name)}
        , predicate_{std::move(pred)}
    {
    }

    // Subscribe with a predicate: the observer only handles events that match it.
    void subscribe(Subject& subject)
    {
        auto self = shared_from_this();
        connection_ = subject.subscribe([wp = std::weak_ptr<FilteredObserver>(self), pred = predicate_](observer_pattern::Event_enum ev) {
            if (!pred(ev)) return;
            if (auto me = wp.lock()) {
                me->update(ev);
            }
        });
    }

    void update(observer_pattern::Event_enum ev)
    {
        std::cout << "[Filtered " << name_ << "] received: " << ev << '\n';
    }

private:
    std::string name_;
    Predicate predicate_;
    Subject::Connection connection_;
};

} // namespace observer_pattern_modern::filtered
