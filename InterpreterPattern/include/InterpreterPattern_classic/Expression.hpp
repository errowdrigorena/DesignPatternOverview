#pragma once

namespace interpreter_pattern_classic {

class Context;

class Expression {
public:
    virtual ~Expression() = default;

    [[nodiscard]] virtual bool interpret(const Context& context) const = 0;
};

}  // namespace interpreter_pattern_classic
