add_executable(PrototypePatternClassicTests
    PrototypePatternClassicTests.cpp
)

target_link_libraries(PrototypePatternClassicTests
    PRIVATE
        PrototypePatternClassic
        GTest::gtest_main
)

target_compile_features(PrototypePatternClassicTests PRIVATE cxx_std_23)

gtest_discover_tests(PrototypePatternClassicTests)

add_executable(PrototypePatternModernTests
    PrototypePatternModernTests.cpp
)

target_link_libraries(PrototypePatternModernTests
    PRIVATE
        PrototypePatternModern
        GTest::gtest_main
)

target_compile_features(PrototypePatternModernTests PRIVATE cxx_std_23)

gtest_discover_tests(PrototypePatternModernTests)
