add_executable(FlyweightPatternClassicTests
    FlyweightPatternClassicTests.cpp
)

target_link_libraries(FlyweightPatternClassicTests
    PRIVATE
        FlyweightPatternClassic
        GTest::gtest_main
)

target_compile_features(FlyweightPatternClassicTests PRIVATE cxx_std_23)

gtest_discover_tests(FlyweightPatternClassicTests)

add_executable(FlyweightPatternModernTests
    FlyweightPatternModernTests.cpp
)

target_link_libraries(FlyweightPatternModernTests
    PRIVATE
        FlyweightPatternModern
        GTest::gtest_main
)

target_compile_features(FlyweightPatternModernTests PRIVATE cxx_std_23)

gtest_discover_tests(FlyweightPatternModernTests)

add_executable(FlyweightPatternModernByKindTests
    FlyweightPatternModernByKindTests.cpp
)

target_link_libraries(FlyweightPatternModernByKindTests
    PRIVATE
        FlyweightPatternModern
        GTest::gtest_main
)

target_compile_features(FlyweightPatternModernByKindTests PRIVATE cxx_std_23)

gtest_discover_tests(FlyweightPatternModernByKindTests)

add_executable(FlyweightPatternModernHandlePoolTests
    FlyweightPatternModernHandlePoolTests.cpp
)

target_link_libraries(FlyweightPatternModernHandlePoolTests
    PRIVATE
        FlyweightPatternModern
        GTest::gtest_main
)

target_compile_features(FlyweightPatternModernHandlePoolTests PRIVATE cxx_std_23)

gtest_discover_tests(FlyweightPatternModernHandlePoolTests)

add_executable(FlyweightPatternModernStaticTableTests
    FlyweightPatternModernStaticTableTests.cpp
)

target_link_libraries(FlyweightPatternModernStaticTableTests
    PRIVATE
        FlyweightPatternModern
        GTest::gtest_main
)

target_compile_features(FlyweightPatternModernStaticTableTests PRIVATE cxx_std_23)

gtest_discover_tests(FlyweightPatternModernStaticTableTests)

add_executable(FlyweightPatternBoostTests
    FlyweightPatternBoostTests.cpp
)

target_link_libraries(FlyweightPatternBoostTests
    PRIVATE
        FlyweightPatternBoost
        GTest::gtest_main
)

target_compile_features(FlyweightPatternBoostTests PRIVATE cxx_std_23)

gtest_discover_tests(FlyweightPatternBoostTests)
