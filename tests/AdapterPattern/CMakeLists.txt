add_executable(AdapterPatternCommonTests
    AdapterPatternCommonTests.cpp
)

target_link_libraries(AdapterPatternCommonTests
    PRIVATE
        AdapterPatternCommon
        GTest::gmock
        GTest::gtest_main
)

target_compile_features(AdapterPatternCommonTests PRIVATE cxx_std_23)

gtest_discover_tests(AdapterPatternCommonTests)

add_executable(AdapterPatternClassicTests
    AdapterPatternClassicTests.cpp
)

target_link_libraries(AdapterPatternClassicTests
    PRIVATE
        AdapterPatternClassic
        GTest::gmock
        GTest::gtest_main
)

target_compile_features(AdapterPatternClassicTests PRIVATE cxx_std_23)

gtest_discover_tests(AdapterPatternClassicTests)

add_executable(AdapterPatternModernTests
    AdapterPatternModernTests.cpp
)

target_link_libraries(AdapterPatternModernTests
    PRIVATE
        AdapterPatternModern
        GTest::gmock
        GTest::gtest_main
)

target_compile_features(AdapterPatternModernTests PRIVATE cxx_std_23)

gtest_discover_tests(AdapterPatternModernTests)
