#pragma once

#include <functional>

namespace command_pattern_modern {

class Command {
public:
    using Action = std::function<void()>;

    // The second action models undo; a minimal command only needs execute.
    Command(Action execute, Action undo);

    void execute() const;
    void undo() const;

private:
    Action execute_;
    Action undo_;
};

}  // namespace command_pattern_modern
