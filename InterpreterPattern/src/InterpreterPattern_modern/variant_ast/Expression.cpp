#include <InterpreterPattern_modern/variant_ast/Expression.hpp>

#include <utility>

namespace interpreter_pattern_modern::variant_ast {

namespace {

template<typename... Callables>
struct Overloaded : Callables... {
    using Callables::operator()...;
};

}  // namespace

Expression::Expression()
    : node{Variable{}}
{
}

Expression::Expression(Node node)
    : node{std::move(node)}
{
}

Expression variable(std::string name)
{
    return Expression{Variable{std::move(name)}};
}

Expression not_(Expression expression)
{
    return Expression{Not{std::make_unique<Expression>(std::move(expression))}};
}

Expression and_(Expression left, Expression right)
{
    return Expression{
        And{
            std::make_unique<Expression>(std::move(left)),
            std::make_unique<Expression>(std::move(right))}};
}

Expression or_(Expression left, Expression right)
{
    return Expression{
        Or{
            std::make_unique<Expression>(std::move(left)),
            std::make_unique<Expression>(std::move(right))}};
}

bool evaluate(const Expression& expression, const interpreter_pattern_classic::Context& context)
{
    return std::visit(
        Overloaded{
            [&context](const Variable& variable) {
                return context.get(variable.name);
            },
            [&context](const Not& not_expression) {
                return !evaluate(*not_expression.expression, context);
            },
            [&context](const And& and_expression) {
                return evaluate(*and_expression.left, context) && evaluate(*and_expression.right, context);
            },
            [&context](const Or& or_expression) {
                return evaluate(*or_expression.left, context) || evaluate(*or_expression.right, context);
            }},
        expression.node);
}

}  // namespace interpreter_pattern_modern::variant_ast
