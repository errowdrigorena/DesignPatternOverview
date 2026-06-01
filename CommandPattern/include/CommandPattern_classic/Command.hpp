#pragma once

namespace command_pattern_classic {

class Command {
public:
    virtual ~Command() = default;

    virtual void execute() = 0;
    // Undo is a common extension of Command, not part of the minimal pattern.
    virtual void undo() = 0;
};

}  // namespace command_pattern_classic
