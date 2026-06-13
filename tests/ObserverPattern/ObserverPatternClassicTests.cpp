#include <ObserverPattern_classic/ConsoleObserver.hpp>
#include <ObserverPattern_classic/Observer.hpp>
#include <ObserverPattern_classic/Subject.hpp>
#include <ObserverPattern_common/Event.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <ostream>
#include <sstream>
#include <vector>

namespace {

using observer_pattern::Event_enum;
using observer_pattern::Subject;
using testing::ElementsAre;
using testing::HasSubstr;
using testing::IsEmpty;

class RecordingObserver final : public observer_pattern::Observer {
public:
    void update(const Event_enum event) override
    {
        events.push_back(event);
    }

    std::vector<Event_enum> events;
};

class SelfUnsubscribingObserver final : public observer_pattern::Observer {
public:
    explicit SelfUnsubscribingObserver(Subject& subject)
        : subject_{subject}
    {
    }

    void update(const Event_enum event) override
    {
        events.push_back(event);
        subject_.unsubscribe(*this);
    }

    std::vector<Event_enum> events;

private:
    Subject& subject_;
};

TEST(EventEnum, StreamsKnownEvents)
{
    std::ostringstream output;

    output << Event_enum::add << ' ' << Event_enum::remove;

    EXPECT_THAT(output.str(), "add remove");
}

TEST(ClassicConsoleObserver, UpdateWritesObserverNameAndEvent)
{
    observer_pattern::ConsoleObserver observer{"screen"};

    testing::internal::CaptureStdout();
    observer.update(Event_enum::add);
    const auto output = testing::internal::GetCapturedStdout();

    EXPECT_THAT(output, HasSubstr("screen got message add"));
}

TEST(ClassicSubject, NotifyUpdatesSubscribedObservers)
{
    Subject subject;
    RecordingObserver first;
    RecordingObserver second;

    subject.subscribe(first);
    subject.subscribe(second);
    subject.notify(Event_enum::add);

    EXPECT_THAT(first.events, ElementsAre(Event_enum::add));
    EXPECT_THAT(second.events, ElementsAre(Event_enum::add));
}

TEST(ClassicSubject, SubscribeIgnoresDuplicateObservers)
{
    Subject subject;
    RecordingObserver observer;

    subject.subscribe(observer);
    subject.subscribe(observer);
    subject.notify(Event_enum::remove);

    EXPECT_THAT(observer.events, ElementsAre(Event_enum::remove));
}

TEST(ClassicSubject, UnsubscribeStopsNotifications)
{
    Subject subject;
    RecordingObserver first;
    RecordingObserver second;

    subject.subscribe(first);
    subject.subscribe(second);
    subject.unsubscribe(first);
    subject.notify(Event_enum::add);

    EXPECT_THAT(first.events, IsEmpty());
    EXPECT_THAT(second.events, ElementsAre(Event_enum::add));
}

TEST(ClassicSubject, ObserverCanUnsubscribeDuringNotification)
{
    Subject subject;
    SelfUnsubscribingObserver self_unsubscribing{subject};
    RecordingObserver remaining;

    subject.subscribe(self_unsubscribing);
    subject.subscribe(remaining);

    subject.notify(Event_enum::add);
    subject.notify(Event_enum::remove);

    EXPECT_THAT(self_unsubscribing.events, ElementsAre(Event_enum::add));
    EXPECT_THAT(remaining.events, ElementsAre(Event_enum::add, Event_enum::remove));
}

}  // namespace
