add_executable(TemplateMethodPatternClassicTests
    TemplateMethodPatternClassicTests.cpp
)

target_link_libraries(TemplateMethodPatternClassicTests
    PRIVATE
        TemplateMethodPatternClassic
        GTest::gmock
        GTest::gtest_main
)

target_compile_features(TemplateMethodPatternClassicTests PRIVATE cxx_std_23)

gtest_discover_tests(TemplateMethodPatternClassicTests)

function(add_template_method_modern_test target source)
    add_executable(${target}
        ${source}
    )

    target_link_libraries(${target}
        PRIVATE
            TemplateMethodPatternModern
            GTest::gmock
            GTest::gtest_main
    )

    target_compile_features(${target} PRIVATE cxx_std_23)

    gtest_discover_tests(${target})
endfunction()

add_template_method_modern_test(
    TemplateMethodPatternCallableTests
    TemplateMethodPatternCallableTests.cpp
)

add_template_method_modern_test(
    TemplateMethodPatternConceptsTests
    TemplateMethodPatternConceptsTests.cpp
)

add_template_method_modern_test(
    TemplateMethodPatternCrtpTests
    TemplateMethodPatternCrtpTests.cpp
)

add_template_method_modern_test(
    TemplateMethodPatternDeducingThisTests
    TemplateMethodPatternDeducingThisTests.cpp
)
