add_executable(ProxyPatternClassicTests ProxyPatternClassicTests.cpp)

target_link_libraries(ProxyPatternClassicTests
    PRIVATE
        ProxyPatternClassic
        GTest::gmock
        GTest::gtest_main
)

target_compile_features(ProxyPatternClassicTests PRIVATE cxx_std_23)

gtest_discover_tests(ProxyPatternClassicTests)

add_executable(ProxyPatternModernTests ProxyPatternModernTests.cpp)

target_link_libraries(ProxyPatternModernTests
    PRIVATE
        ProxyPatternModern
        GTest::gmock
        GTest::gtest_main
)

target_compile_features(ProxyPatternModernTests PRIVATE cxx_std_23)

gtest_discover_tests(ProxyPatternModernTests)
