add_library(TemplateMethodPatternClassic
    src/TemplateMethodPattern_classic/ReportGenerator.cpp
    src/TemplateMethodPattern_classic/AuditReportGenerator.cpp
    src/TemplateMethodPattern_classic/SalesReportGenerator.cpp
)

target_include_directories(TemplateMethodPatternClassic
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(TemplateMethodPatternClassic PUBLIC cxx_std_23)

add_library(TemplateMethodPatternModern INTERFACE)

target_include_directories(TemplateMethodPatternModern
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(TemplateMethodPatternModern INTERFACE cxx_std_23)

add_executable(TemplateMethodPatternDemo
    src/TemplateMethodPatternDemo.cpp
)

target_link_libraries(TemplateMethodPatternDemo
    PRIVATE
        TemplateMethodPatternClassic
)

function(add_template_method_modern_demo target source)
    add_executable(${target}
        ${source}
    )

    target_link_libraries(${target}
        PRIVATE
            TemplateMethodPatternModern
    )
endfunction()

add_template_method_modern_demo(
    TemplateMethodPatternModernCrtpDemo
    src/TemplateMethodPatternModernCrtpDemo.cpp
)

add_template_method_modern_demo(
    TemplateMethodPatternModernConceptsDemo
    src/TemplateMethodPatternModernConceptsDemo.cpp
)

add_template_method_modern_demo(
    TemplateMethodPatternModernCallableDemo
    src/TemplateMethodPatternModernCallableDemo.cpp
)

add_template_method_modern_demo(
    TemplateMethodPatternModernDeducingThisDemo
    src/TemplateMethodPatternModernDeducingThisDemo.cpp
)
