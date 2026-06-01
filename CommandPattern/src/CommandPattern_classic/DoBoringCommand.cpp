#include <CommandPattern_classic/DoBoringCommand.hpp>

#include <iostream>

namespace command_pattern_classic {

void DoBoringCommand::execute()
{
    std::cout << "doing something boring\n";
}

void DoBoringCommand::undo()
{
    std::cout << "undoing something boring\n";
}

}  // namespace command_pattern_classic
