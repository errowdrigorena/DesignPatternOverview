#include <InterpreterPattern_classic/Context.hpp>
#include <InterpreterPattern_modern/bison_rules/BisonRuleParser.hpp>

#include <iostream>

int main()
{
    namespace bison_rules = interpreter_pattern_modern::bison_rules;

    interpreter_pattern_classic::Context context;
    context.set("cliente_vip", true);
    context.set("compra_mayor_100", true);
    context.set("usuario_bloqueado", false);

    const auto rule = bison_rules::parse_rule(
        "cliente_vip &&& compra_mayor_100 &&& !! usuario_bloqueado");

    std::cout << "Bison rule: "
              << (bison_rules::evaluate(*rule, context) ? "accepted" : "rejected")
              << '\n';

    return 0;
}
