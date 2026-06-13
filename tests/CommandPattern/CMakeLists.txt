add_executable(CommandPatternClassicTests
    CommandPatternClassicTests.cpp
)

target_link_libraries(CommandPatternClassicTests
    PRIVATE
        CommandPatternClassic
        GTest::gmock
        GTest::gtest_main
)

target_include_directories(CommandPatternClassicTests
    PRIVATE
        ${CMAKE_SOURCE_DIR}/tests
)

target_compile_features(CommandPatternClassicTests PRIVATE cxx_std_23)

gtest_discover_tests(CommandPatternClassicTests)

add_executable(CommandPatternModernTests
    CommandPatternModernTests.cpp
)

target_link_libraries(CommandPatternModernTests
    PRIVATE
        CommandPatternModern
        GTest::gmock
        GTest::gtest_main
)

target_compile_features(CommandPatternModernTests PRIVATE cxx_std_23)

gtest_discover_tests(CommandPatternModernTests)
