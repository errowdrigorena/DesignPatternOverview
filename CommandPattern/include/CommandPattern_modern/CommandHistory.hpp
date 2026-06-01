#pragma once

#include <CommandPattern_modern/Command.hpp>

#include <vector>

namespace command_pattern_modern {

// The history is an optional invoker feature, useful for undo stacks.
class CommandHistory {
public:
    void execute(Command command);
    void undo_last();

private:
    std::vector<Command> commands_;
};

}  // namespace command_pattern_modern
