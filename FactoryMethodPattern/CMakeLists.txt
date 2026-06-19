add_library(FactoryMethodPatternClassic
    src/FactoryMethodPattern_classic/CircleCreator.cpp
    src/FactoryMethodPattern_classic/RectangleCreator.cpp
    src/FactoryMethodPattern_classic/TriangleCreator.cpp
)

target_include_directories(FactoryMethodPatternClassic
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(FactoryMethodPatternClassic PUBLIC cxx_std_23)

target_link_libraries(FactoryMethodPatternClassic
    PUBLIC
        Shapes_traditional
)

add_library(FactoryMethodPatternSimpleFactory INTERFACE)

target_include_directories(FactoryMethodPatternSimpleFactory
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(FactoryMethodPatternSimpleFactory INTERFACE cxx_std_23)

target_link_libraries(FactoryMethodPatternSimpleFactory
    INTERFACE
        SimpleFactoryPseudoPatternSwitch
)

add_library(FactoryMethodPatternModern INTERFACE)

target_include_directories(FactoryMethodPatternModern
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(FactoryMethodPatternModern INTERFACE cxx_std_23)

target_link_libraries(FactoryMethodPatternModern
    INTERFACE
        Shapes_traditional
        SimpleFactoryPseudoPatternSwitch
)

add_executable(FactoryMethodPatternDemo
    src/FactoryMethodPatternDemo.cpp
)

target_link_libraries(FactoryMethodPatternDemo
    PRIVATE
        FactoryMethodPatternClassic
)

add_executable(FactoryMethodPatternSimpleFactoryDemo
    src/FactoryMethodPatternSimpleFactoryDemo.cpp
)

target_link_libraries(FactoryMethodPatternSimpleFactoryDemo
    PRIVATE
        FactoryMethodPatternSimpleFactory
)

add_executable(FactoryMethodPatternModernDemo
    src/FactoryMethodPatternModernDemo.cpp
)

target_link_libraries(FactoryMethodPatternModernDemo
    PRIVATE
        FactoryMethodPatternModern
)
