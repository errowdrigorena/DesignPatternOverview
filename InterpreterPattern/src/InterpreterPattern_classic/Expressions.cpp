#include <InterpreterPattern_classic/Context.hpp>
#include <InterpreterPattern_classic/Expressions.hpp>

#include <stdexcept>
#include <utility>

namespace interpreter_pattern_classic {

void Context::set(std::string name, bool value)
{
    values_[std::move(name)] = value;
}

bool Context::get(const std::string& name) const
{
    const auto it = values_.find(name);
    if(it == values_.end()) {
        throw std::out_of_range{"Unknown variable in interpreter context: " + name};
    }

    return it->second;
}

bool Context::contains(const std::string& name) const
{
    return values_.contains(name);
}

VariableExpression::VariableExpression(std::string name)
    : name_{std::move(name)}
{
}

bool VariableExpression::interpret(const Context& context) const
{
    return context.get(name_);
}

NotExpression::NotExpression(std::unique_ptr<Expression> expression)
    : expression_{std::move(expression)}
{
}

bool NotExpression::interpret(const Context& context) const
{
    return !expression_->interpret(context);
}

AndExpression::AndExpression(std::unique_ptr<Expression> left, std::unique_ptr<Expression> right)
    : left_{std::move(left)}
    , right_{std::move(right)}
{
}

bool AndExpression::interpret(const Context& context) const
{
    return left_->interpret(context) && right_->interpret(context);
}

OrExpression::OrExpression(std::unique_ptr<Expression> left, std::unique_ptr<Expression> right)
    : left_{std::move(left)}
    , right_{std::move(right)}
{
}

bool OrExpression::interpret(const Context& context) const
{
    return left_->interpret(context) || right_->interpret(context);
}

}  // namespace interpreter_pattern_classic
