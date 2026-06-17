#include <InterpreterPattern_classic/Context.hpp>
#include <InterpreterPattern_modern/bison_rules/BisonRuleParser.hpp>

#include <gtest/gtest.h>

#include <stdexcept>

namespace {

namespace bison_rules = interpreter_pattern_modern::bison_rules;

interpreter_pattern_classic::Context discount_context()
{
    interpreter_pattern_classic::Context context;
    context.set("cliente_vip", true);
    context.set("compra_mayor_100", true);
    context.set("usuario_bloqueado", false);
    context.set("producto_en_oferta", false);
    context.set("cupon_activo", true);
    return context;
}

TEST(ModernBisonRulesInterpreter, ParsesVerboseOperatorNames)
{
    const auto rule = bison_rules::parse_rule(
        "cliente_vip AND compra_mayor_100 AND NOT usuario_bloqueado");

    EXPECT_TRUE(bison_rules::evaluate(*rule, discount_context()));
}

TEST(ModernBisonRulesInterpreter, ParsesSymbolicOperatorAliases)
{
    const auto rule = bison_rules::parse_rule(
        "cliente_vip &&& compra_mayor_100 &&& !! usuario_bloqueado");

    EXPECT_TRUE(bison_rules::evaluate(*rule, discount_context()));
}

TEST(ModernBisonRulesInterpreter, ParsesOrWithBothSpellings)
{
    const auto symbolic_rule = bison_rules::parse_rule("producto_en_oferta ||| cupon_activo");
    const auto verbose_rule = bison_rules::parse_rule("producto_en_oferta OR cupon_activo");
    const auto context = discount_context();

    EXPECT_TRUE(bison_rules::evaluate(*symbolic_rule, context));
    EXPECT_TRUE(bison_rules::evaluate(*verbose_rule, context));
}

TEST(ModernBisonRulesInterpreter, HonorsParentheses)
{
    const auto rule = bison_rules::parse_rule(
        "(producto_en_oferta OR cupon_activo) AND !! usuario_bloqueado");

    EXPECT_TRUE(bison_rules::evaluate(*rule, discount_context()));
}

TEST(ModernBisonRulesInterpreter, RejectsInvalidSyntax)
{
    EXPECT_THROW(
        static_cast<void>(bison_rules::parse_rule("cliente_vip AND AND cupon_activo")),
        std::invalid_argument);
}

}  // namespace
