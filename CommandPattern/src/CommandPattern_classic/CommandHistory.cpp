#include <CommandPattern_classic/CommandHistory.hpp>

#include <utility>

namespace command_pattern_classic {

void CommandHistory::execute(std::unique_ptr<Command> command)
{
    command->execute();
    commands_.push_back(std::move(command));
}

void CommandHistory::undo_last()
{
    if (commands_.empty()) {
        return;
    }

    commands_.back()->undo();
    commands_.pop_back();
}

}  // namespace command_pattern_classic
