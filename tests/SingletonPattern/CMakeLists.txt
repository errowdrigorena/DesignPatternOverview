add_executable(SingletonPatternTests
    SingletonPatternTests.cpp
)

target_link_libraries(SingletonPatternTests
    PRIVATE
        SingletonPattern
        SingletonPatternModern
        GTest::gmock
        GTest::gtest_main
)

target_compile_features(SingletonPatternTests PRIVATE cxx_std_23)

gtest_discover_tests(SingletonPatternTests)
