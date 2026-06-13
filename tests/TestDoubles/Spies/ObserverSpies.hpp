#pragma once

#include <ObserverPattern_classic/Observer.hpp>
#include <ObserverPattern_classic/Subject.hpp>
#include <ObserverPattern_common/Event.hpp>

#include <vector>

namespace test_doubles::spies {

class RecordingObserver final : public observer_pattern::Observer {
public:
    void update(const observer_pattern::Event_enum event) override
    {
        events.push_back(event);
    }

    std::vector<observer_pattern::Event_enum> events;
};

class SelfUnsubscribingObserver final : public observer_pattern::Observer {
public:
    explicit SelfUnsubscribingObserver(observer_pattern::Subject& subject)
        : subject_{subject}
    {
    }

    void update(const observer_pattern::Event_enum event) override
    {
        events.push_back(event);
        subject_.unsubscribe(*this);
    }

    std::vector<observer_pattern::Event_enum> events;

private:
    observer_pattern::Subject& subject_;
};

}  // namespace test_doubles::spies
