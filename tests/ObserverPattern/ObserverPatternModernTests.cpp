#include <ObserverPattern_common/Event.hpp>
#include <ObserverPattern_modern/filtered/FilteredObserver.hpp>
#include <ObserverPattern_modern/signal_slot/ConsoleObserver.hpp>
#include <ObserverPattern_modern/signal_slot/Signal.hpp>
#include <ObserverPattern_modern/signal_slot/Subject.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>
#include <stdexcept>
#include <vector>

namespace {

using observer_pattern::Event_enum;
using observer_pattern_modern::Signal;
using testing::ElementsAre;
using testing::HasSubstr;
using testing::IsEmpty;
using testing::Throws;

TEST(ModernSignal, EmitCallsConnectedSlotsInOrder)
{
    Signal<Event_enum> signal;
    std::vector<Event_enum> first_events;
    std::vector<Event_enum> second_events;

    auto first_connection = signal.connect([&first_events](const Event_enum event) {
        first_events.push_back(event);
    });
    auto second_connection = signal.connect([&second_events](const Event_enum event) {
        second_events.push_back(event);
    });

    signal.emit(Event_enum::add);

    EXPECT_TRUE(first_connection.connected());
    EXPECT_TRUE(second_connection.connected());
    EXPECT_THAT(first_events, ElementsAre(Event_enum::add));
    EXPECT_THAT(second_events, ElementsAre(Event_enum::add));
}

TEST(ModernSignal, RejectsEmptySlot)
{
    Signal<Event_enum> signal;

    const auto connect_empty_slot = [&signal] {
        [[maybe_unused]] auto connection = signal.connect(typename Signal<Event_enum>::Slot{});
    };

    EXPECT_THAT(connect_empty_slot, Throws<std::invalid_argument>());
}

TEST(ModernSignal, DisconnectStopsNotifications)
{
    Signal<Event_enum> signal;
    std::vector<Event_enum> events;

    auto connection = signal.connect([&events](const Event_enum event) {
        events.push_back(event);
    });

    signal.emit(Event_enum::add);
    connection.disconnect();
    signal.emit(Event_enum::remove);

    EXPECT_FALSE(connection.connected());
    EXPECT_THAT(events, ElementsAre(Event_enum::add));
}

TEST(ModernSignal, ConnectionDisconnectsOnDestruction)
{
    Signal<Event_enum> signal;
    std::vector<Event_enum> events;

    {
        auto connection = signal.connect([&events](const Event_enum event) {
            events.push_back(event);
        });
        EXPECT_TRUE(connection.connected());
    }

    signal.emit(Event_enum::add);

    EXPECT_THAT(events, IsEmpty());
}

TEST(ModernSignal, MoveTransfersConnectionOwnership)
{
    Signal<Event_enum> signal;
    std::vector<Event_enum> events;

    auto first = signal.connect([&events](const Event_enum event) {
        events.push_back(event);
    });
    auto second = std::move(first);

    EXPECT_FALSE(first.connected());
    EXPECT_TRUE(second.connected());

    signal.emit(Event_enum::remove);

    EXPECT_THAT(events, ElementsAre(Event_enum::remove));
}

TEST(ModernSignal, DisconnectDuringEmitDoesNotCallDisconnectedSlot)
{
    Signal<Event_enum> signal;
    std::vector<Event_enum> first_events;
    std::vector<Event_enum> second_events;
    typename Signal<Event_enum>::Connection second_connection;

    auto first_connection = signal.connect([&](const Event_enum event) {
        first_events.push_back(event);
        second_connection.disconnect();
    });
    second_connection = signal.connect([&](const Event_enum event) {
        second_events.push_back(event);
    });

    signal.emit(Event_enum::add);

    EXPECT_TRUE(first_connection.connected());
    EXPECT_FALSE(second_connection.connected());
    EXPECT_THAT(first_events, ElementsAre(Event_enum::add));
    EXPECT_THAT(second_events, IsEmpty());
}

TEST(ModernSubject, NotifyEmitsToSubscribers)
{
    observer_pattern_modern::Subject subject;
    std::vector<Event_enum> events;

    auto connection = subject.subscribe([&events](const Event_enum event) {
        events.push_back(event);
    });

    subject.notify(Event_enum::add);
    subject.notify(Event_enum::remove);

    EXPECT_TRUE(connection.connected());
    EXPECT_THAT(events, ElementsAre(Event_enum::add, Event_enum::remove));
}

TEST(ModernConsoleObserver, SubscribeReceivesSubjectNotifications)
{
    observer_pattern_modern::Subject subject;
    auto observer = std::make_shared<observer_pattern_modern::ConsoleObserver>("screen");

    observer->subscribe(subject);

    testing::internal::CaptureStdout();
    subject.notify(Event_enum::add);
    const auto output = testing::internal::GetCapturedStdout();

    EXPECT_THAT(output, HasSubstr("[Modern screen] event: add"));
}

TEST(ModernFilteredObserver, SubscribeOnlyReceivesMatchingEvents)
{
    observer_pattern_modern::Subject subject;
    auto observer = std::make_shared<observer_pattern_modern::filtered::FilteredObserver>(
        "add_only",
        [](const Event_enum event) {
            return event == Event_enum::add;
        });

    observer->subscribe(subject);

    testing::internal::CaptureStdout();
    subject.notify(Event_enum::remove);
    subject.notify(Event_enum::add);
    const auto output = testing::internal::GetCapturedStdout();

    EXPECT_THAT(output, HasSubstr("[Filtered add_only] received: add"));
    EXPECT_THAT(output, testing::Not(HasSubstr("remove")));
}

TEST(ModernFilteredObserver, DefaultPredicateReceivesAllEvents)
{
    observer_pattern_modern::Subject subject;
    auto observer = std::make_shared<observer_pattern_modern::filtered::FilteredObserver>("all");

    observer->subscribe(subject);

    testing::internal::CaptureStdout();
    subject.notify(Event_enum::remove);
    const auto output = testing::internal::GetCapturedStdout();

    EXPECT_THAT(output, HasSubstr("[Filtered all] received: remove"));
}

}  // namespace
