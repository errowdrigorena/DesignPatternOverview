add_executable(CompositePatternClassicTests
    CompositePatternClassicTests.cpp
)

target_link_libraries(CompositePatternClassicTests
    PRIVATE
        CompositePatternClassic
        GTest::gmock
        GTest::gtest_main
)

target_compile_features(CompositePatternClassicTests PRIVATE cxx_std_23)

gtest_discover_tests(CompositePatternClassicTests)

add_executable(CompositePatternModernTests
    CompositePatternModernTests.cpp
)

target_link_libraries(CompositePatternModernTests
    PRIVATE
        CompositePatternModern
        GTest::gmock
        GTest::gtest_main
)

target_compile_features(CompositePatternModernTests PRIVATE cxx_std_23)

gtest_discover_tests(CompositePatternModernTests)
