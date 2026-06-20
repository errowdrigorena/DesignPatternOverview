add_executable(BuilderPatternClassicTests BuilderPatternClassicTests.cpp)

target_link_libraries(BuilderPatternClassicTests
    PRIVATE
        BuilderPatternClassic
        GTest::gtest_main
)

target_compile_features(BuilderPatternClassicTests PRIVATE cxx_std_23)

gtest_discover_tests(BuilderPatternClassicTests)

add_executable(BuilderPatternModernTests BuilderPatternModernTests.cpp)

target_link_libraries(BuilderPatternModernTests
    PRIVATE
        BuilderPatternModern
        GTest::gtest_main
)

target_compile_features(BuilderPatternModernTests PRIVATE cxx_std_23)

gtest_discover_tests(BuilderPatternModernTests)
