#include <ObserverPattern_common/Event.hpp>
#include <ObserverPattern_modern/Signal.hpp>

#include <iostream>
#include <string_view>

namespace {

auto print_message(std::string_view observer_name)
{
    return [observer_name](const observer_pattern::Event_enum event) {
        std::cout << observer_name << " got message " << event << '\n';
    };
}

}  // namespace

int main()
{
    observer_pattern_modern::Signal<observer_pattern::Event_enum> message_signal;

    auto observer_a_connection = message_signal.connect(print_message("observerA"));
    auto observer_b_connection = message_signal.connect(print_message("observerB"));
    auto observer_c_connection = message_signal.connect(print_message("observerC"));

    message_signal.emit(observer_pattern::Event_enum::add);
    observer_b_connection.disconnect();
    message_signal.emit(observer_pattern::Event_enum::remove);

    return 0;
}
