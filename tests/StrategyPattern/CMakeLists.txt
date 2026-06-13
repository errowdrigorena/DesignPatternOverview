add_executable(StrategyPatternClassicTests
    StrategyPatternClassicTests.cpp
)

target_link_libraries(StrategyPatternClassicTests
    PRIVATE
        StrategyPattern
        GTest::gmock
        GTest::gtest_main
)

target_include_directories(StrategyPatternClassicTests
    PRIVATE
        ${CMAKE_SOURCE_DIR}/tests
)

target_compile_features(StrategyPatternClassicTests PRIVATE cxx_std_23)

gtest_discover_tests(StrategyPatternClassicTests)

add_executable(StrategyPatternFunctionTests
    StrategyPatternFunctionTests.cpp
)

target_link_libraries(StrategyPatternFunctionTests
    PRIVATE
        StrategyPatternFunction
        GTest::gmock
        GTest::gtest_main
)

target_include_directories(StrategyPatternFunctionTests
    PRIVATE
        ${CMAKE_SOURCE_DIR}/tests
)

target_compile_features(StrategyPatternFunctionTests PRIVATE cxx_std_23)

gtest_discover_tests(StrategyPatternFunctionTests)
