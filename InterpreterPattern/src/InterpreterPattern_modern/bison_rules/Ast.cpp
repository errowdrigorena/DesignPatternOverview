#include <InterpreterPattern_modern/bison_rules/Ast.hpp>

#include <utility>

namespace interpreter_pattern_modern::bison_rules {

VariableExpression::VariableExpression(std::string name)
    : name_{std::move(name)}
{
}

bool VariableExpression::evaluate(const interpreter_pattern_classic::Context& context) const
{
    return context.get(name_);
}

NotExpression::NotExpression(ExpressionPtr expression)
    : expression_{std::move(expression)}
{
}

bool NotExpression::evaluate(const interpreter_pattern_classic::Context& context) const
{
    return !expression_->evaluate(context);
}

AndExpression::AndExpression(ExpressionPtr left, ExpressionPtr right)
    : left_{std::move(left)}
    , right_{std::move(right)}
{
}

bool AndExpression::evaluate(const interpreter_pattern_classic::Context& context) const
{
    return left_->evaluate(context) && right_->evaluate(context);
}

OrExpression::OrExpression(ExpressionPtr left, ExpressionPtr right)
    : left_{std::move(left)}
    , right_{std::move(right)}
{
}

bool OrExpression::evaluate(const interpreter_pattern_classic::Context& context) const
{
    return left_->evaluate(context) || right_->evaluate(context);
}

ExpressionPtr variable(std::string name)
{
    return std::make_unique<VariableExpression>(std::move(name));
}

ExpressionPtr not_(ExpressionPtr expression)
{
    return std::make_unique<NotExpression>(std::move(expression));
}

ExpressionPtr and_(ExpressionPtr left, ExpressionPtr right)
{
    return std::make_unique<AndExpression>(std::move(left), std::move(right));
}

ExpressionPtr or_(ExpressionPtr left, ExpressionPtr right)
{
    return std::make_unique<OrExpression>(std::move(left), std::move(right));
}

bool evaluate(const Expression& expression, const interpreter_pattern_classic::Context& context)
{
    return expression.evaluate(context);
}

}  // namespace interpreter_pattern_modern::bison_rules
