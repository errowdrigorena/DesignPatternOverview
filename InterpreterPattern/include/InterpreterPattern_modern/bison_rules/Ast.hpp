#pragma once

#include <InterpreterPattern_classic/Context.hpp>

#include <memory>
#include <string>

namespace interpreter_pattern_modern::bison_rules {

class Expression {
public:
    virtual ~Expression() = default;

    [[nodiscard]] virtual bool evaluate(const interpreter_pattern_classic::Context& context) const = 0;
};

using ExpressionPtr = std::unique_ptr<Expression>;

class VariableExpression final : public Expression {
public:
    explicit VariableExpression(std::string name);

    [[nodiscard]] bool evaluate(const interpreter_pattern_classic::Context& context) const override;

private:
    std::string name_;
};

class NotExpression final : public Expression {
public:
    explicit NotExpression(ExpressionPtr expression);

    [[nodiscard]] bool evaluate(const interpreter_pattern_classic::Context& context) const override;

private:
    ExpressionPtr expression_;
};

class AndExpression final : public Expression {
public:
    AndExpression(ExpressionPtr left, ExpressionPtr right);

    [[nodiscard]] bool evaluate(const interpreter_pattern_classic::Context& context) const override;

private:
    ExpressionPtr left_;
    ExpressionPtr right_;
};

class OrExpression final : public Expression {
public:
    OrExpression(ExpressionPtr left, ExpressionPtr right);

    [[nodiscard]] bool evaluate(const interpreter_pattern_classic::Context& context) const override;

private:
    ExpressionPtr left_;
    ExpressionPtr right_;
};

[[nodiscard]] ExpressionPtr variable(std::string name);
[[nodiscard]] ExpressionPtr not_(ExpressionPtr expression);
[[nodiscard]] ExpressionPtr and_(ExpressionPtr left, ExpressionPtr right);
[[nodiscard]] ExpressionPtr or_(ExpressionPtr left, ExpressionPtr right);

[[nodiscard]] bool evaluate(const Expression& expression, const interpreter_pattern_classic::Context& context);

}  // namespace interpreter_pattern_modern::bison_rules
