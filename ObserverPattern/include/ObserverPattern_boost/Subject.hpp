#pragma once

#include <ObserverPattern_common/Event.hpp>

#include <boost/signals2/signal.hpp>

namespace observer_pattern_boost {

// boost::signals2::signal is a thread-safe, RAII-based implementation of
// the Observer pattern. Connections are automatically cleaned up when
// a scoped_connection goes out of scope.
class Subject {
public:
    using SignalT = boost::signals2::signal<void(observer_pattern::Event_enum)>;
    using Connection = boost::signals2::scoped_connection;

    template <typename Slot>
    [[nodiscard]] Connection subscribe(Slot&& slot)
    {
        return Connection{signal_.connect(std::forward<Slot>(slot))};
    }

    void notify(observer_pattern::Event_enum event)
    {
        signal_(event);
    }

private:
    SignalT signal_;
};

}  // namespace observer_pattern_boost
