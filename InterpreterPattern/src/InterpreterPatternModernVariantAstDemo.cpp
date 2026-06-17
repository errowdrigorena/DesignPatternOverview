#include <InterpreterPattern_classic/Context.hpp>
#include <InterpreterPattern_modern/variant_ast/Expression.hpp>

#include <iostream>

int main()
{
    namespace ast = interpreter_pattern_modern::variant_ast;

    interpreter_pattern_classic::Context context;
    context.set("cliente_vip", true);
    context.set("compra_mayor_100", true);
    context.set("usuario_bloqueado", false);

    auto rule = ast::and_(
        ast::and_(
            ast::variable("cliente_vip"),
            ast::variable("compra_mayor_100")),
        ast::not_(ast::variable("usuario_bloqueado")));

    std::cout << "variant AST rule: "
              << (ast::evaluate(rule, context) ? "accepted" : "rejected")
              << '\n';

    return 0;
}
