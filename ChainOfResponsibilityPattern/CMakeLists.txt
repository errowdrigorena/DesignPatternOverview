add_library(ChainOfResponsibilityPatternClassic
    src/ChainOfResponsibilityPattern_classic/ShapeRequestHandler.cpp
    src/ChainOfResponsibilityPattern_classic/DrawShapeHandler.cpp
    src/ChainOfResponsibilityPattern_classic/AreaShapeHandler.cpp
)

target_include_directories(ChainOfResponsibilityPatternClassic
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(ChainOfResponsibilityPatternClassic PUBLIC cxx_std_23)

target_link_libraries(ChainOfResponsibilityPatternClassic
    PUBLIC
        Shapes_traditional
)

add_library(ChainOfResponsibilityPatternModern
    src/ChainOfResponsibilityPattern_modern/ShapeRequestChain.cpp
)

target_include_directories(ChainOfResponsibilityPatternModern
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(ChainOfResponsibilityPatternModern PUBLIC cxx_std_23)

target_link_libraries(ChainOfResponsibilityPatternModern
    PUBLIC
        Shapes_traditional
)

add_executable(ChainOfResponsibilityPatternDemo
    src/ChainOfResponsibilityPatternDemo.cpp
)

target_link_libraries(ChainOfResponsibilityPatternDemo
    PRIVATE
        ChainOfResponsibilityPatternClassic
)

add_executable(ChainOfResponsibilityPatternModernDemo
    src/ChainOfResponsibilityPatternModernDemo.cpp
)

target_link_libraries(ChainOfResponsibilityPatternModernDemo
    PRIVATE
        ChainOfResponsibilityPatternModern
)
