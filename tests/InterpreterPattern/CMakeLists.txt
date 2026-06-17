add_executable(InterpreterPatternClassicTests
    InterpreterPatternClassicTests.cpp
)

target_link_libraries(InterpreterPatternClassicTests
    PRIVATE
        InterpreterPatternClassic
        GTest::gmock
        GTest::gtest_main
)

target_compile_features(InterpreterPatternClassicTests PRIVATE cxx_std_23)

gtest_discover_tests(InterpreterPatternClassicTests)

add_executable(InterpreterPatternModernVariantAstTests
    InterpreterPatternModernVariantAstTests.cpp
)

target_link_libraries(InterpreterPatternModernVariantAstTests
    PRIVATE
        InterpreterPatternModernVariantAst
        GTest::gmock
        GTest::gtest_main
)

target_compile_features(InterpreterPatternModernVariantAstTests PRIVATE cxx_std_23)

gtest_discover_tests(InterpreterPatternModernVariantAstTests)

add_executable(InterpreterPatternModernBisonRulesTests
    InterpreterPatternModernBisonRulesTests.cpp
)

target_link_libraries(InterpreterPatternModernBisonRulesTests
    PRIVATE
        InterpreterPatternModernBisonRules
        GTest::gmock
        GTest::gtest_main
)

target_compile_features(InterpreterPatternModernBisonRulesTests PRIVATE cxx_std_23)

gtest_discover_tests(InterpreterPatternModernBisonRulesTests)
