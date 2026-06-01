#pragma once

#include <CommandPattern_classic/Command.hpp>

namespace command_pattern_classic {

class DoBoringCommand final : public Command {
public:
    void execute() override;
    void undo() override;
};

}  // namespace command_pattern_classic
