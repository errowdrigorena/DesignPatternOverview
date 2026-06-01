#include <ObserverPattern_classic/ConsoleObserver.hpp>
#include <ObserverPattern_common/Event.hpp>
#include <ObserverPattern_classic/Subject.hpp>

int main()
{
    observer_pattern::ConsoleObserver observer_a{"observerA"};
    observer_pattern::ConsoleObserver observer_b{"observerB"};
    observer_pattern::ConsoleObserver observer_c{"observerC"};

    observer_pattern::Subject subject;
    subject.subscribe(observer_a);
    subject.subscribe(observer_b);
    subject.subscribe(observer_c);

    subject.notify(observer_pattern::Event_enum::add);
    
    subject.unsubscribe(observer_b);
    subject.notify(observer_pattern::Event_enum::remove);

    return 0;
}
