#pragma once

#include "InterpreterPatternModernBisonParser.hpp"

#include <string>
#include <string_view>

namespace interpreter_pattern_modern::bison_rules {

// Exposed for teaching: it lets the course show how the lexer feeds Bison.
// In production code, this would normally stay in a private/source-only area.
class Scanner {
public:
    explicit Scanner(std::string_view input);

    [[nodiscard]] RuleParser::symbol_type next_token();

private:
    void skip_whitespace();
    [[nodiscard]] bool is_at_end() const;
    [[nodiscard]] char peek() const;
    [[nodiscard]] bool starts_with(std::string_view text) const;
    [[nodiscard]] std::string read_identifier();

    std::string_view input_;
    std::size_t position_{};
};

}  // namespace interpreter_pattern_modern::bison_rules
