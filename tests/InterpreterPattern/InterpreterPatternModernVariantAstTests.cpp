#include <InterpreterPattern_classic/Context.hpp>
#include <InterpreterPattern_modern/variant_ast/Expression.hpp>

#include <gtest/gtest.h>

#include <stdexcept>

namespace {

namespace ast = interpreter_pattern_modern::variant_ast;

TEST(ModernVariantAstInterpreter, EvaluatesComposedBooleanRules)
{
    interpreter_pattern_classic::Context context;
    context.set("cliente_vip", true);
    context.set("compra_mayor_100", true);
    context.set("usuario_bloqueado", false);

    auto rule = ast::and_(
        ast::and_(
            ast::variable("cliente_vip"),
            ast::variable("compra_mayor_100")),
        ast::not_(ast::variable("usuario_bloqueado")));

    EXPECT_TRUE(ast::evaluate(rule, context));
}

TEST(ModernVariantAstInterpreter, PreservesAndShortCircuiting)
{
    interpreter_pattern_classic::Context context;
    context.set("cliente_vip", false);

    auto rule = ast::and_(
        ast::variable("cliente_vip"),
        ast::variable("undefined_variable"));

    EXPECT_FALSE(ast::evaluate(rule, context));
}

TEST(ModernVariantAstInterpreter, PreservesOrShortCircuiting)
{
    interpreter_pattern_classic::Context context;
    context.set("cupon_activo", true);

    auto rule = ast::or_(
        ast::variable("cupon_activo"),
        ast::variable("undefined_variable"));

    EXPECT_TRUE(ast::evaluate(rule, context));
}

TEST(ModernVariantAstInterpreter, ThrowsWhenVariableIsMissing)
{
    const interpreter_pattern_classic::Context context;
    auto rule = ast::variable("missing");

    EXPECT_THROW(static_cast<void>(ast::evaluate(rule, context)), std::out_of_range);
}

}  // namespace
