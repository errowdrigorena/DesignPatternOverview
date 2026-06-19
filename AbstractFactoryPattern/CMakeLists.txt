add_library(AbstractFactoryPatternClassic
    src/AbstractFactoryPattern_classic/SolidShapeFactory.cpp
    src/AbstractFactoryPattern_classic/WireframeShapeFactory.cpp
    src/AbstractFactoryPattern_classic/ShapeScene.cpp
    src/AbstractFactoryPattern_common/SolidShapes/SolidCircle.cpp
    src/AbstractFactoryPattern_common/SolidShapes/SolidRectangle.cpp
    src/AbstractFactoryPattern_common/SolidShapes/SolidTriangle.cpp
    src/AbstractFactoryPattern_common/WireframeShapes/WireframeCircle.cpp
    src/AbstractFactoryPattern_common/WireframeShapes/WireframeRectangle.cpp
    src/AbstractFactoryPattern_common/WireframeShapes/WireframeTriangle.cpp
)

target_include_directories(AbstractFactoryPatternClassic
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(AbstractFactoryPatternClassic PUBLIC cxx_std_23)

target_link_libraries(AbstractFactoryPatternClassic
    PUBLIC
        Shapes_traditional
)

add_library(AbstractFactoryPatternModern
    src/AbstractFactoryPattern_modern/ShapeFamilyFactory.cpp
    src/AbstractFactoryPattern_modern/ShapeScene.cpp
)

target_include_directories(AbstractFactoryPatternModern
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(AbstractFactoryPatternModern PUBLIC cxx_std_23)

target_link_libraries(AbstractFactoryPatternModern
    PUBLIC
        AbstractFactoryPatternClassic
)

add_executable(AbstractFactoryPatternDemo
    src/AbstractFactoryPatternDemo.cpp
)

target_link_libraries(AbstractFactoryPatternDemo
    PRIVATE
        AbstractFactoryPatternClassic
)

add_executable(AbstractFactoryPatternModernDemo
    src/AbstractFactoryPatternModernDemo.cpp
)

target_link_libraries(AbstractFactoryPatternModernDemo
    PRIVATE
        AbstractFactoryPatternModern
)
