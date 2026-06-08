#pragma once

#include <ObserverPattern_common/Event.hpp>
#include <ObserverPattern_modern/signal_slot/Signal.hpp>

namespace observer_pattern_modern {

class Subject {
public:
    using SignalT = Signal<observer_pattern::Event_enum>;
    using Connection = typename SignalT::Connection;

    Subject() = default;

    // Subscribe with any callable matching Slot (returns a Connection RAII handle)
    Connection subscribe(typename SignalT::Slot slot)
    {
        return signal_.connect(std::move(slot));
    }

    void notify(observer_pattern::Event_enum event)
    {
        signal_.emit(event);
    }

private:
    SignalT signal_;
};

} // namespace observer_pattern_modern
