add_executable(SimpleFactoryPseudoPatternRuntimeTests
    SimpleFactoryPseudoPatternRuntimeTests.cpp
)

target_link_libraries(SimpleFactoryPseudoPatternRuntimeTests
    PRIVATE
        SimpleFactoryPseudoPatternSwitch
        SimpleFactoryPseudoPatternMap
        SimpleFactoryPseudoPatternStatic
        GTest::gmock
        GTest::gtest_main
)

target_compile_features(SimpleFactoryPseudoPatternRuntimeTests PRIVATE cxx_std_23)

gtest_discover_tests(SimpleFactoryPseudoPatternRuntimeTests)

add_executable(SimpleFactoryPseudoPatternTemplateTests
    SimpleFactoryPseudoPatternTemplateTests.cpp
)

target_link_libraries(SimpleFactoryPseudoPatternTemplateTests
    PRIVATE
        SimpleFactoryPseudoPatternTemplate
        GTest::gmock
        GTest::gtest_main
)

target_compile_features(SimpleFactoryPseudoPatternTemplateTests PRIVATE cxx_std_23)

gtest_discover_tests(SimpleFactoryPseudoPatternTemplateTests)
