add_library(Shapes_modern
    src/Shapes_modern/Circle.cpp
    src/Shapes_modern/Rectangle.cpp
    src/Shapes_modern/Triangle.cpp
)

target_include_directories(Shapes_modern
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(Shapes_modern PUBLIC cxx_std_23)

add_library(Shapes_traditional
    src/Shapes_traditional/Circle.cpp
    src/Shapes_traditional/Rectangle.cpp
    src/Shapes_traditional/Triangle.cpp
)

target_include_directories(Shapes_traditional
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(Shapes_traditional PUBLIC cxx_std_23)

add_executable(ShapesModernDemo
    src/ShapesModernDemo.cpp
)

target_link_libraries(ShapesModernDemo
    PRIVATE
        Shapes_modern
)

add_executable(ShapesTraditionalDemo
    src/ShapesTraditionalDemo.cpp
)

target_link_libraries(ShapesTraditionalDemo
    PRIVATE
        Shapes_traditional
)
