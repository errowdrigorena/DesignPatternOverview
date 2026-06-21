add_executable(IteratorPatternClassicTests IteratorPatternClassicTests.cpp)

target_link_libraries(IteratorPatternClassicTests
    PRIVATE
        IteratorPatternClassic
        GTest::gtest_main
)

target_compile_features(IteratorPatternClassicTests PRIVATE cxx_std_23)

gtest_discover_tests(IteratorPatternClassicTests)

add_executable(IteratorPatternModernIteratorsTests IteratorPatternModernIteratorsTests.cpp)

target_link_libraries(IteratorPatternModernIteratorsTests
    PRIVATE
        IteratorPatternModernIterators
        GTest::gtest_main
)

target_compile_features(IteratorPatternModernIteratorsTests PRIVATE cxx_std_23)

gtest_discover_tests(IteratorPatternModernIteratorsTests)

add_executable(IteratorPatternModernRangesTests IteratorPatternModernRangesTests.cpp)

target_link_libraries(IteratorPatternModernRangesTests
    PRIVATE
        IteratorPatternModernRanges
        GTest::gtest_main
)

target_compile_features(IteratorPatternModernRangesTests PRIVATE cxx_std_23)

gtest_discover_tests(IteratorPatternModernRangesTests)
