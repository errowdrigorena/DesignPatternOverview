#include <ObserverPattern_common/Event.hpp>
#include <ObserverPattern_modern/filtered/FilteredObserver.hpp>
#include <ObserverPattern_modern/signal_slot/Subject.hpp>

#include <iostream>
#include <memory>

int main()
{
    observer_pattern_modern::Subject subject;

    auto add_only = std::make_shared<observer_pattern_modern::filtered::FilteredObserver>(
        "add_only",
        [](const observer_pattern::Event_enum ev) {
            return ev == observer_pattern::Event_enum::add;
        });

    auto remove_only = std::make_shared<observer_pattern_modern::filtered::FilteredObserver>(
        "remove_only",
        [](const observer_pattern::Event_enum ev) {
            return ev == observer_pattern::Event_enum::remove;
        });

    auto all_events = std::make_shared<observer_pattern_modern::filtered::FilteredObserver>(
        "all_events");

    add_only->subscribe(subject);
    remove_only->subscribe(subject);
    all_events->subscribe(subject);

    std::cout << "-- notify add --\n";
    subject.notify(observer_pattern::Event_enum::add);

    std::cout << "\n-- notify remove --\n";
    subject.notify(observer_pattern::Event_enum::remove);

    return 0;
}
