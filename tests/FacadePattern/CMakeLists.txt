add_executable(FacadePatternClassicTests
    FacadePatternClassicTests.cpp
)

target_link_libraries(FacadePatternClassicTests
    PRIVATE
        FacadePatternClassic
        GTest::gmock
        GTest::gtest_main
)

target_compile_features(FacadePatternClassicTests PRIVATE cxx_std_23)

gtest_discover_tests(FacadePatternClassicTests)
