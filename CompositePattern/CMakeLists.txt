add_library(CompositePatternClassic
    src/CompositePattern_classic/ShapeLeaf.cpp
    src/CompositePattern_classic/ShapeGroup.cpp
)

target_include_directories(CompositePatternClassic
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(CompositePatternClassic PUBLIC cxx_std_23)

add_library(CompositePatternModern
    src/CompositePattern_modern/GraphicNode.cpp
)

target_include_directories(CompositePatternModern
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(CompositePatternModern PUBLIC cxx_std_23)

add_executable(CompositePatternDemo
    src/CompositePatternDemo.cpp
)

target_link_libraries(CompositePatternDemo
    PRIVATE
        CompositePatternClassic
)

add_executable(CompositePatternModernDemo
    src/CompositePatternModernDemo.cpp
)

target_link_libraries(CompositePatternModernDemo
    PRIVATE
        CompositePatternModern
)
