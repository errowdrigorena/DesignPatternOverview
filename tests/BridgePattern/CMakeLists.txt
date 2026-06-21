add_executable(BridgePatternClassicTests BridgePatternClassicTests.cpp)

target_link_libraries(BridgePatternClassicTests
    PRIVATE
        BridgePatternClassic
        GTest::gtest_main
)

target_compile_features(BridgePatternClassicTests PRIVATE cxx_std_23)

gtest_discover_tests(BridgePatternClassicTests)

add_executable(BridgePatternModernTests BridgePatternModernTests.cpp)

target_link_libraries(BridgePatternModernTests
    PRIVATE
        BridgePatternModern
        GTest::gtest_main
)

target_compile_features(BridgePatternModernTests PRIVATE cxx_std_23)

gtest_discover_tests(BridgePatternModernTests)
