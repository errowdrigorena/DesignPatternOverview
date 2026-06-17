add_library(InterpreterPatternClassic
    src/InterpreterPattern_classic/Expressions.cpp
)

target_include_directories(InterpreterPatternClassic
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(InterpreterPatternClassic PUBLIC cxx_std_23)

add_library(InterpreterPatternModernVariantAst
    src/InterpreterPattern_modern/variant_ast/Expression.cpp
)

target_include_directories(InterpreterPatternModernVariantAst
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(InterpreterPatternModernVariantAst PUBLIC cxx_std_23)

target_link_libraries(InterpreterPatternModernVariantAst
    PUBLIC
        InterpreterPatternClassic
)

find_package(BISON REQUIRED)

BISON_TARGET(InterpreterPatternModernBisonParser
    src/InterpreterPattern_modern/bison_rules/RuleParser.y
    ${CMAKE_CURRENT_BINARY_DIR}/generated/InterpreterPatternModernBisonParser.cpp
    DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/generated/InterpreterPatternModernBisonParser.hpp
)

add_library(InterpreterPatternModernBisonRules
    src/InterpreterPattern_modern/bison_rules/Ast.cpp
    src/InterpreterPattern_modern/bison_rules/BisonRuleParser.cpp
    ${BISON_InterpreterPatternModernBisonParser_OUTPUTS}
)

target_include_directories(InterpreterPatternModernBisonRules
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_BINARY_DIR}/generated
)

target_compile_features(InterpreterPatternModernBisonRules PUBLIC cxx_std_23)

target_link_libraries(InterpreterPatternModernBisonRules
    PUBLIC
        InterpreterPatternClassic
)

add_executable(InterpreterPatternDemo
    src/InterpreterPatternDemo.cpp
)

target_link_libraries(InterpreterPatternDemo
    PRIVATE
        InterpreterPatternClassic
)

add_executable(InterpreterPatternModernVariantAstDemo
    src/InterpreterPatternModernVariantAstDemo.cpp
)

target_link_libraries(InterpreterPatternModernVariantAstDemo
    PRIVATE
        InterpreterPatternModernVariantAst
)

add_executable(InterpreterPatternModernBisonRulesDemo
    src/InterpreterPatternModernBisonRulesDemo.cpp
)

target_link_libraries(InterpreterPatternModernBisonRulesDemo
    PRIVATE
        InterpreterPatternModernBisonRules
)
