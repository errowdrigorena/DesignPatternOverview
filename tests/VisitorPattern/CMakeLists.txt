add_executable(VisitorPatternClassicTests
    VisitorPatternClassicTests.cpp
)

target_link_libraries(VisitorPatternClassicTests
    PRIVATE
        VisitorPatternClassic
        GTest::gmock
        GTest::gtest_main
)

target_compile_features(VisitorPatternClassicTests PRIVATE cxx_std_23)

gtest_discover_tests(VisitorPatternClassicTests)

add_executable(VisitorPatternModernTests
    VisitorPatternModernTests.cpp
)

target_link_libraries(VisitorPatternModernTests
    PRIVATE
        VisitorPatternModern
        GTest::gmock
        GTest::gtest_main
)

target_compile_features(VisitorPatternModernTests PRIVATE cxx_std_23)

gtest_discover_tests(VisitorPatternModernTests)
