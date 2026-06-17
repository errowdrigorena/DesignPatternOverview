#include <InterpreterPattern_classic/Context.hpp>
#include <InterpreterPattern_classic/Expressions.hpp>

#include <gtest/gtest.h>

#include <memory>
#include <stdexcept>

namespace {

using interpreter_pattern_classic::AndExpression;
using interpreter_pattern_classic::Context;
using interpreter_pattern_classic::NotExpression;
using interpreter_pattern_classic::OrExpression;
using interpreter_pattern_classic::VariableExpression;

TEST(ClassicContext, StoresAndReadsNamedValues)
{
    Context context;

    context.set("cliente_vip", true);
    context.set("usuario_bloqueado", false);

    EXPECT_TRUE(context.contains("cliente_vip"));
    EXPECT_TRUE(context.get("cliente_vip"));
    EXPECT_FALSE(context.get("usuario_bloqueado"));
}

TEST(ClassicContext, ThrowsWhenVariableIsUnknown)
{
    const Context context;

    EXPECT_THROW(static_cast<void>(context.get("missing")), std::out_of_range);
}

TEST(ClassicVariableExpression, ReadsValueFromContext)
{
    Context context;
    context.set("compra_mayor_100", true);

    const VariableExpression expression{"compra_mayor_100"};

    EXPECT_TRUE(expression.interpret(context));
}

TEST(ClassicBooleanExpressions, CombineRulesWithAndOrAndNot)
{
    Context context;
    context.set("cliente_vip", true);
    context.set("compra_mayor_100", true);
    context.set("usuario_bloqueado", false);

    auto rule = std::make_unique<AndExpression>(
        std::make_unique<AndExpression>(
            std::make_unique<VariableExpression>("cliente_vip"),
            std::make_unique<VariableExpression>("compra_mayor_100")),
        std::make_unique<NotExpression>(
            std::make_unique<VariableExpression>("usuario_bloqueado")));

    EXPECT_TRUE(rule->interpret(context));
}

TEST(ClassicBooleanExpressions, OrAcceptsAnyTrueBranch)
{
    Context context;
    context.set("producto_en_oferta", false);
    context.set("cupon_activo", true);

    const OrExpression rule{
        std::make_unique<VariableExpression>("producto_en_oferta"),
        std::make_unique<VariableExpression>("cupon_activo")};

    EXPECT_TRUE(rule.interpret(context));
}

TEST(ClassicBooleanExpressions, AndShortCircuitsRightBranch)
{
    Context context;
    context.set("cliente_vip", false);

    const AndExpression rule{
        std::make_unique<VariableExpression>("cliente_vip"),
        std::make_unique<VariableExpression>("variable_no_definida")};

    EXPECT_FALSE(rule.interpret(context));
}

TEST(ClassicBooleanExpressions, OrShortCircuitsRightBranch)
{
    Context context;
    context.set("cupon_activo", true);

    const OrExpression rule{
        std::make_unique<VariableExpression>("cupon_activo"),
        std::make_unique<VariableExpression>("variable_no_definida")};

    EXPECT_TRUE(rule.interpret(context));
}

}  // namespace
