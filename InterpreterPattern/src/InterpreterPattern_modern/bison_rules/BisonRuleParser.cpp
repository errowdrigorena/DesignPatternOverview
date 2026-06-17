#include <InterpreterPattern_modern/bison_rules/BisonRuleParser.hpp>

#include <InterpreterPattern_modern/bison_rules/Scanner.hpp>

#include <cctype>
#include <stdexcept>
#include <string>
#include <utility>

namespace interpreter_pattern_modern::bison_rules {

Scanner::Scanner(std::string_view input)
    : input_{input}
{
}

RuleParser::symbol_type Scanner::next_token()
{
    skip_whitespace();

    if(is_at_end()) {
        return RuleParser::make_YYEOF();
    }

    if(starts_with("&&&")) {
        position_ += 3;
        return RuleParser::make_AND();
    }

    if(starts_with("|||")) {
        position_ += 3;
        return RuleParser::make_OR();
    }

    if(starts_with("!!")) {
        position_ += 2;
        return RuleParser::make_NOT();
    }

    if(peek() == '(') {
        ++position_;
        return RuleParser::make_LPAREN();
    }

    if(peek() == ')') {
        ++position_;
        return RuleParser::make_RPAREN();
    }

    if(std::isalpha(static_cast<unsigned char>(peek())) != 0 || peek() == '_') {
        auto identifier = read_identifier();

        if(identifier == "AND") {
            return RuleParser::make_AND();
        }

        if(identifier == "OR") {
            return RuleParser::make_OR();
        }

        if(identifier == "NOT") {
            return RuleParser::make_NOT();
        }

        return RuleParser::make_IDENTIFIER(std::move(identifier));
    }

    throw std::invalid_argument{"Unexpected character in Bison interpreter rule"};
}

void Scanner::skip_whitespace()
{
    while(!is_at_end() && std::isspace(static_cast<unsigned char>(peek())) != 0) {
        ++position_;
    }
}

bool Scanner::is_at_end() const
{
    return position_ >= input_.size();
}

char Scanner::peek() const
{
    return input_[position_];
}

bool Scanner::starts_with(std::string_view text) const
{
    return input_.substr(position_, text.size()) == text;
}

std::string Scanner::read_identifier()
{
    const auto start = position_;

    while(!is_at_end()) {
        const auto current = static_cast<unsigned char>(peek());
        if(std::isalnum(current) == 0 && peek() != '_') {
            break;
        }

        ++position_;
    }

    return std::string{input_.substr(start, position_ - start)};
}

void RuleParser::error(const std::string& message)
{
    throw std::invalid_argument{"Invalid Bison interpreter rule: " + message};
}

ExpressionPtr parse_rule(std::string_view rule)
{
    Scanner scanner{rule};
    ExpressionPtr result;
    RuleParser parser{scanner, result};

    if(parser.parse() != 0) {
        throw std::invalid_argument{"Invalid Bison interpreter rule"};
    }

    return result;
}

}  // namespace interpreter_pattern_modern::bison_rules
