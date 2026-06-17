%skeleton "lalr1.cc"
%require "3.8.2"
%defines

%define api.namespace {interpreter_pattern_modern::bison_rules}
%define api.parser.class {RuleParser}
%define api.token.constructor
%define api.value.type variant
%define parse.error verbose

%param {Scanner& scanner}
%param {ExpressionPtr& result}

%code requires {
    #include <InterpreterPattern_modern/bison_rules/Ast.hpp>

    #include <string>

    namespace interpreter_pattern_modern::bison_rules {
    class Scanner;
    }
}

%code {
    #include <InterpreterPattern_modern/bison_rules/Scanner.hpp>

    namespace interpreter_pattern_modern::bison_rules {
    static RuleParser::symbol_type yylex(Scanner& scanner, ExpressionPtr&)
    {
        return scanner.next_token();
    }
    }
}

%token <std::string> IDENTIFIER
%token NOT
%token AND
%token OR
%token LPAREN
%token RPAREN

%nterm <ExpressionPtr> expression

%left OR
%left AND
%right NOT

%%

input:
    expression
    {
        result = std::move($1);
    }
;

expression:
    IDENTIFIER
    {
        $$ = variable(std::move($1));
    }
  | NOT expression
    {
        $$ = not_(std::move($2));
    }
  | expression AND expression
    {
        $$ = and_(std::move($1), std::move($3));
    }
  | expression OR expression
    {
        $$ = or_(std::move($1), std::move($3));
    }
  | LPAREN expression RPAREN
    {
        $$ = std::move($2);
    }
;

%%
