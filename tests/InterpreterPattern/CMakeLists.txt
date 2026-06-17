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
