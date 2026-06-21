add_executable(ChainOfResponsibilityPatternClassicTests ChainOfResponsibilityPatternClassicTests.cpp)

target_link_libraries(ChainOfResponsibilityPatternClassicTests
    PRIVATE
        ChainOfResponsibilityPatternClassic
        GTest::gtest_main
)

target_compile_features(ChainOfResponsibilityPatternClassicTests PRIVATE cxx_std_23)

gtest_discover_tests(ChainOfResponsibilityPatternClassicTests)

add_executable(ChainOfResponsibilityPatternModernTests ChainOfResponsibilityPatternModernTests.cpp)

target_link_libraries(ChainOfResponsibilityPatternModernTests
    PRIVATE
        ChainOfResponsibilityPatternModern
        GTest::gtest_main
)

target_compile_features(ChainOfResponsibilityPatternModernTests PRIVATE cxx_std_23)

gtest_discover_tests(ChainOfResponsibilityPatternModernTests)
