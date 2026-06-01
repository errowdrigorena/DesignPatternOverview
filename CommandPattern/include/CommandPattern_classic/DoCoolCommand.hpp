#pragma once

#include <CommandPattern_classic/Command.hpp>

namespace command_pattern_classic {

class DoCoolCommand final : public Command {
public:
    void execute() override;
    void undo() override; // optional
};

}  // namespace command_pattern_classic
