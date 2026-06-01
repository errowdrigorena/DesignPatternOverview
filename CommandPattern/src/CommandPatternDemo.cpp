#include <CommandPattern_classic/CommandHistory.hpp>
#include <CommandPattern_classic/DoBoringCommand.hpp>
#include <CommandPattern_classic/DoCoolCommand.hpp>

#include <memory>

int main()
{
    command_pattern_classic::CommandHistory history;

    history.execute(std::make_unique<command_pattern_classic::DoCoolCommand>());
    history.execute(std::make_unique<command_pattern_classic::DoBoringCommand>());
    history.undo_last();
    history.undo_last();

    return 0;
}
