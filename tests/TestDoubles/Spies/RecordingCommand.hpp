#pragma once

#include <CommandPattern_classic/Command.hpp>

#include <string>
#include <utility>
#include <vector>

namespace test_doubles::spies {

class RecordingCommand final : public command_pattern_classic::Command {
public:
    RecordingCommand(std::vector<std::string>& events, std::string name)
        : events_{events}
        , name_{std::move(name)}
    {
    }

    void execute() override
    {
        events_.push_back("execute " + name_);
    }

    void undo() override
    {
        events_.push_back("undo " + name_);
    }

private:
    std::vector<std::string>& events_;
    std::string name_;
};

}  // namespace test_doubles::spies
