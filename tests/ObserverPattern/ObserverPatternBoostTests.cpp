#include <ObserverPattern_boost/Subject.hpp>
#include <ObserverPattern_common/Event.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <vector>

namespace {

using observer_pattern::Event_enum;
using observer_pattern_boost::Subject;
using testing::ElementsAre;
using testing::IsEmpty;

TEST(BoostSignals2Subject, EmitNotifiesAllSubscribers)
{
    Subject subject;
    std::vector<Event_enum> first_events;
    std::vector<Event_enum> second_events;

    auto conn_a = subject.subscribe([&first_events](Event_enum e) { first_events.push_back(e); });
    auto conn_b = subject.subscribe([&second_events](Event_enum e) { second_events.push_back(e); });

    subject.notify(Event_enum::add);

    EXPECT_THAT(first_events, ElementsAre(Event_enum::add));
    EXPECT_THAT(second_events, ElementsAre(Event_enum::add));
}

TEST(BoostSignals2Subject, ScopedConnectionDisconnectsOnDestruction)
{
    Subject subject;
    std::vector<Event_enum> events;

    {
        auto conn = subject.subscribe([&events](Event_enum e) { events.push_back(e); });
        subject.notify(Event_enum::add);
    }

    subject.notify(Event_enum::remove);

    EXPECT_THAT(events, ElementsAre(Event_enum::add));
}

TEST(BoostSignals2Subject, ExplicitDisconnectStopsNotifications)
{
    Subject subject;
    std::vector<Event_enum> events;

    auto conn = subject.subscribe([&events](Event_enum e) { events.push_back(e); });
    subject.notify(Event_enum::add);
    conn.release().disconnect();
    subject.notify(Event_enum::remove);

    EXPECT_THAT(events, ElementsAre(Event_enum::add));
}

TEST(BoostSignals2Subject, MultipleSubscribersReceiveEventsInOrder)
{
    Subject subject;
    std::vector<std::string> log;

    auto conn_a = subject.subscribe([&log](Event_enum) { log.push_back("A"); });
    auto conn_b = subject.subscribe([&log](Event_enum) { log.push_back("B"); });
    auto conn_c = subject.subscribe([&log](Event_enum) { log.push_back("C"); });

    subject.notify(Event_enum::add);

    EXPECT_THAT(log, ElementsAre("A", "B", "C"));
}

TEST(BoostSignals2Subject, NoSubscribersIsValid)
{
    Subject subject;
    EXPECT_NO_THROW(subject.notify(Event_enum::add));
}

}  // namespace
