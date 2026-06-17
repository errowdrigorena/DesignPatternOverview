#pragma once

#include <InterpreterPattern_classic/Context.hpp>

#include <memory>
#include <string>
#include <variant>

namespace interpreter_pattern_modern::variant_ast {

struct Expression;

struct Variable {
    std::string name;
};

struct Not {
    std::unique_ptr<Expression> expression;
};

struct And {
    std::unique_ptr<Expression> left;
    std::unique_ptr<Expression> right;
};

struct Or {
    std::unique_ptr<Expression> left;
    std::unique_ptr<Expression> right;
};

struct Expression {
    using Node = std::variant<Variable, Not, And, Or>;

    Expression();
    explicit Expression(Node node);

    Node node;
};

[[nodiscard]] Expression variable(std::string name);
[[nodiscard]] Expression not_(Expression expression);
[[nodiscard]] Expression and_(Expression left, Expression right);
[[nodiscard]] Expression or_(Expression left, Expression right);

[[nodiscard]] bool evaluate(const Expression& expression, const interpreter_pattern_classic::Context& context);

}  // namespace interpreter_pattern_modern::variant_ast
