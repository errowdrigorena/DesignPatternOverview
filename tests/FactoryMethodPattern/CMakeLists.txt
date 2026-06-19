add_executable(FactoryMethodPatternClassicTests
    FactoryMethodPatternClassicTests.cpp
)

target_link_libraries(FactoryMethodPatternClassicTests
    PRIVATE
        FactoryMethodPatternClassic
        GTest::gmock
        GTest::gtest_main
)

target_compile_features(FactoryMethodPatternClassicTests PRIVATE cxx_std_23)

gtest_discover_tests(FactoryMethodPatternClassicTests)

add_executable(FactoryMethodPatternSimpleFactoryTests
    FactoryMethodPatternSimpleFactoryTests.cpp
)

target_link_libraries(FactoryMethodPatternSimpleFactoryTests
    PRIVATE
        FactoryMethodPatternSimpleFactory
        GTest::gmock
        GTest::gtest_main
)

target_compile_features(FactoryMethodPatternSimpleFactoryTests PRIVATE cxx_std_23)

gtest_discover_tests(FactoryMethodPatternSimpleFactoryTests)

add_executable(FactoryMethodPatternModernTests
    FactoryMethodPatternModernTests.cpp
)

target_link_libraries(FactoryMethodPatternModernTests
    PRIVATE
        FactoryMethodPatternModern
        GTest::gmock
        GTest::gtest_main
)

target_compile_features(FactoryMethodPatternModernTests PRIVATE cxx_std_23)

gtest_discover_tests(FactoryMethodPatternModernTests)
