#include <ObserverPattern_boost/Subject.hpp>
#include <ObserverPattern_common/Event.hpp>

#include <iostream>
#include <string_view>

namespace {

auto print_message(std::string_view name)
{
    return [name](const observer_pattern::Event_enum event) {
        std::cout << name << " got event: " << event << '\n';
    };
}

}  // namespace

int main()
{
    observer_pattern_boost::Subject subject;

    auto conn_a = subject.subscribe(print_message("observerA"));
    auto conn_b = subject.subscribe(print_message("observerB"));
    auto conn_c = subject.subscribe(print_message("observerC"));

    subject.notify(observer_pattern::Event_enum::add);

    conn_b.release().disconnect();

    subject.notify(observer_pattern::Event_enum::remove);
}
