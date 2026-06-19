add_executable(AbstractFactoryPatternClassicTests
    AbstractFactoryPatternClassicTests.cpp
)

target_link_libraries(AbstractFactoryPatternClassicTests
    PRIVATE
        AbstractFactoryPatternClassic
        GTest::gmock
        GTest::gtest_main
)

target_compile_features(AbstractFactoryPatternClassicTests PRIVATE cxx_std_23)

gtest_discover_tests(AbstractFactoryPatternClassicTests)

add_executable(AbstractFactoryPatternModernTests
    AbstractFactoryPatternModernTests.cpp
)

target_link_libraries(AbstractFactoryPatternModernTests
    PRIVATE
        AbstractFactoryPatternModern
        GTest::gmock
        GTest::gtest_main
)

target_compile_features(AbstractFactoryPatternModernTests PRIVATE cxx_std_23)

gtest_discover_tests(AbstractFactoryPatternModernTests)
