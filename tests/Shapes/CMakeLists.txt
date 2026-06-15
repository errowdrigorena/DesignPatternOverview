add_executable(ShapesTraditionalTests
    ShapesTraditionalTests.cpp
)

target_link_libraries(ShapesTraditionalTests
    PRIVATE
        Shapes_traditional
        GTest::gmock
        GTest::gtest_main
)

target_compile_features(ShapesTraditionalTests PRIVATE cxx_std_23)

gtest_discover_tests(ShapesTraditionalTests)

add_executable(ShapesModernTests
    ShapesModernTests.cpp
)

target_link_libraries(ShapesModernTests
    PRIVATE
        Shapes_modern
        GTest::gmock
        GTest::gtest_main
)

target_compile_features(ShapesModernTests PRIVATE cxx_std_23)

gtest_discover_tests(ShapesModernTests)
