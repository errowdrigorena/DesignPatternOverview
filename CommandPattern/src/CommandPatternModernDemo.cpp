#include <CommandPattern_modern/Command.hpp>
#include <CommandPattern_modern/CommandHistory.hpp>

#include <iostream>

namespace {

command_pattern_modern::Command make_do_cool_command()
{
    return command_pattern_modern::Command{
        [] {
            std::cout << "doing something cool\n";
        },
        [] {
            std::cout << "undoing something cool\n";
        }};
}

command_pattern_modern::Command make_do_boring_command()
{
    return command_pattern_modern::Command{
        [] {
            std::cout << "doing something boring\n";
        },
        [] {
            std::cout << "undoing something boring\n";
        }};
}

}  // namespace

int main()
{
    command_pattern_modern::CommandHistory history;

    history.execute(make_do_cool_command());
    history.execute(make_do_boring_command());
    history.undo_last();
    history.undo_last();

    return 0;
}
