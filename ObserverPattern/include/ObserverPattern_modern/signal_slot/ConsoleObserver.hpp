#pragma once

#include <ObserverPattern_common/Event.hpp>
#include <ObserverPattern_modern/signal_slot/Signal.hpp>
#include <ObserverPattern_modern/signal_slot/Subject.hpp>

#include <memory>
#include <string>
#include <iostream>

namespace observer_pattern_modern {

class ConsoleObserver : public std::enable_shared_from_this<ConsoleObserver> {
public:
    explicit ConsoleObserver(std::string name)
        : name_{std::move(name)}
    {
    }

    // Subscribe this observer to a subject. The observer stores the Connection
    // so it will automatically disconnect when destroyed.
    void subscribe(Subject& subject)
    {
        auto self = shared_from_this();
        connection_ = subject.subscribe([wp = std::weak_ptr<ConsoleObserver>(self)](observer_pattern::Event_enum ev) {
            if (auto me = wp.lock()) {
                me->update(ev);
            }
        });
    }

    void update(observer_pattern::Event_enum ev)
    {
        std::cout << "[Modern " << name_ << "] event: " << ev << '\n';
    }

private:
    std::string name_;
    Signal<observer_pattern::Event_enum>::Connection connection_;
};

} // namespace observer_pattern_modern
