add_executable(ObserverPatternClassicTests
    ObserverPatternClassicTests.cpp
)

target_link_libraries(ObserverPatternClassicTests
    PRIVATE
        ObserverPattern
        GTest::gmock
        GTest::gtest_main
)

target_compile_features(ObserverPatternClassicTests PRIVATE cxx_std_23)

gtest_discover_tests(ObserverPatternClassicTests)

add_executable(ObserverPatternModernTests
    ObserverPatternModernTests.cpp
)

target_link_libraries(ObserverPatternModernTests
    PRIVATE
        ObserverPatternModern
        GTest::gmock
        GTest::gtest_main
)

target_compile_features(ObserverPatternModernTests PRIVATE cxx_std_23)

gtest_discover_tests(ObserverPatternModernTests)
