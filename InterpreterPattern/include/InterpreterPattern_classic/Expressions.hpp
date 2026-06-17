#pragma once

#include <InterpreterPattern_classic/Expression.hpp>

#include <memory>
#include <string>

namespace interpreter_pattern_classic {

class VariableExpression final : public Expression {
public:
    explicit VariableExpression(std::string name);

    [[nodiscard]] bool interpret(const Context& context) const override;

private:
    std::string name_;
};

class NotExpression final : public Expression {
public:
    explicit NotExpression(std::unique_ptr<Expression> expression);

    [[nodiscard]] bool interpret(const Context& context) const override;

private:
    std::unique_ptr<Expression> expression_;
};

class AndExpression final : public Expression {
public:
    AndExpression(std::unique_ptr<Expression> left, std::unique_ptr<Expression> right);

    [[nodiscard]] bool interpret(const Context& context) const override;

private:
    std::unique_ptr<Expression> left_;
    std::unique_ptr<Expression> right_;
};

class OrExpression final : public Expression {
public:
    OrExpression(std::unique_ptr<Expression> left, std::unique_ptr<Expression> right);

    [[nodiscard]] bool interpret(const Context& context) const override;

private:
    std::unique_ptr<Expression> left_;
    std::unique_ptr<Expression> right_;
};

}  // namespace interpreter_pattern_classic
