#include <InterpreterPattern_classic/Context.hpp>
#include <InterpreterPattern_classic/Expressions.hpp>

#include <iostream>
#include <memory>
#include <string_view>

namespace {

using interpreter_pattern_classic::AndExpression;
using interpreter_pattern_classic::Context;
using interpreter_pattern_classic::Expression;
using interpreter_pattern_classic::NotExpression;
using interpreter_pattern_classic::OrExpression;
using interpreter_pattern_classic::VariableExpression;

std::unique_ptr<Expression> build_discount_rule()
{
    // cliente_vip AND compra_mayor_100 AND NOT usuario_bloqueado
    return std::make_unique<AndExpression>(
        std::make_unique<AndExpression>(
            std::make_unique<VariableExpression>("cliente_vip"),
            std::make_unique<VariableExpression>("compra_mayor_100")),
        std::make_unique<NotExpression>(
            std::make_unique<VariableExpression>("usuario_bloqueado")));
}

std::unique_ptr<Expression> build_promotion_rule()
{
    // producto_en_oferta OR cupon_activo
    return std::make_unique<OrExpression>(
        std::make_unique<VariableExpression>("producto_en_oferta"),
        std::make_unique<VariableExpression>("cupon_activo"));
}

void print_result(std::string_view rule_name, const Expression& rule, const Context& context)
{
    std::cout << rule_name << ": "
              << (rule.interpret(context) ? "accepted" : "rejected")
              << '\n';
}

}  // namespace

int main()
{
    Context first_customer;
    first_customer.set("cliente_vip", true);
    first_customer.set("compra_mayor_100", true);
    first_customer.set("usuario_bloqueado", false);
    first_customer.set("producto_en_oferta", false);
    first_customer.set("cupon_activo", true);

    Context blocked_customer;
    blocked_customer.set("cliente_vip", true);
    blocked_customer.set("compra_mayor_100", true);
    blocked_customer.set("usuario_bloqueado", true);
    blocked_customer.set("producto_en_oferta", false);
    blocked_customer.set("cupon_activo", false);

    const auto discount_rule = build_discount_rule();
    const auto promotion_rule = build_promotion_rule();

    std::cout << "Customer A\n";
    print_result("discount rule", *discount_rule, first_customer);
    print_result("promotion rule", *promotion_rule, first_customer);

    std::cout << "\nCustomer B\n";
    print_result("discount rule", *discount_rule, blocked_customer);
    print_result("promotion rule", *promotion_rule, blocked_customer);

    return 0;
}
