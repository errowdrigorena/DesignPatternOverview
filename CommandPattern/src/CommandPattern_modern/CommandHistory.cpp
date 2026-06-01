#include <CommandPattern_modern/CommandHistory.hpp>

#include <stdexcept>
#include <utility>

namespace command_pattern_modern {

Command::Command(Action execute, Action undo)
    : execute_{std::move(execute)}
    , undo_{std::move(undo)}
{
    if (!execute_ || !undo_) {
        throw std::invalid_argument{"command actions cannot be empty"};
    }
}

void Command::execute() const
{
    execute_();
}

void Command::undo() const
{
    undo_();
}

void CommandHistory::execute(Command command)
{
    command.execute();
    commands_.push_back(std::move(command));
}

void CommandHistory::undo_last()
{
    if (commands_.empty()) {
        return;
    }

    commands_.back().undo();
    commands_.pop_back();
}

}  // namespace command_pattern_modern
