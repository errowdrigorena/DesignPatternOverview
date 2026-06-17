#pragma once

#include <InterpreterPattern_modern/bison_rules/Ast.hpp>

#include <string_view>

namespace interpreter_pattern_modern::bison_rules {

[[nodiscard]] ExpressionPtr parse_rule(std::string_view rule);

}  // namespace interpreter_pattern_modern::bison_rules
