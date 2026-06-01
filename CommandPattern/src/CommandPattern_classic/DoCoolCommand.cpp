#include <CommandPattern_classic/DoCoolCommand.hpp>

#include <iostream>

namespace command_pattern_classic {

void DoCoolCommand::execute()
{
    std::cout << "doing something cool\n";
}

void DoCoolCommand::undo()
{
    std::cout << "undoing something cool\n";
}

}  // namespace command_pattern_classic
