add_executable(DecoratorPatternClassicTests
    DecoratorPatternClassicTests.cpp
)

target_link_libraries(DecoratorPatternClassicTests
    PRIVATE
        DecoratorPatternClassic
        GTest::gmock
        GTest::gtest_main
)

target_compile_features(DecoratorPatternClassicTests PRIVATE cxx_std_23)

gtest_discover_tests(DecoratorPatternClassicTests)

add_executable(DecoratorPatternModernTests
    DecoratorPatternModernTests.cpp
)

target_link_libraries(DecoratorPatternModernTests
    PRIVATE
        DecoratorPatternModern
        GTest::gmock
        GTest::gtest_main
)

target_compile_features(DecoratorPatternModernTests PRIVATE cxx_std_23)

gtest_discover_tests(DecoratorPatternModernTests)
