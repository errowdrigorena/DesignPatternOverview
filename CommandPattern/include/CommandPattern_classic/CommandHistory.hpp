#pragma once

#include <CommandPattern_classic/Command.hpp>

#include <memory>
#include <vector>

namespace command_pattern_classic {

// The history is only needed because this example teaches undo as well.
class CommandHistory {
public:
    void execute(std::unique_ptr<Command> command);
    void undo_last();

private:
    std::vector<std::unique_ptr<Command>> commands_;
};

}  // namespace command_pattern_classic
