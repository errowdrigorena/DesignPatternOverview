add_executable(MediatorPatternClassicTests MediatorPatternClassicTests.cpp)

target_link_libraries(MediatorPatternClassicTests
    PRIVATE
        MediatorPatternClassic
        GTest::gtest_main
)

target_compile_features(MediatorPatternClassicTests PRIVATE cxx_std_23)

gtest_discover_tests(MediatorPatternClassicTests)

add_executable(MediatorPatternModernTests MediatorPatternModernTests.cpp)

target_link_libraries(MediatorPatternModernTests
    PRIVATE
        MediatorPatternModern
        GTest::gtest_main
)

target_compile_features(MediatorPatternModernTests PRIVATE cxx_std_23)

gtest_discover_tests(MediatorPatternModernTests)
