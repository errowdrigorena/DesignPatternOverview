add_library(PrototypePatternClassic
    src/PrototypePattern_classic/CirclePrototype.cpp
    src/PrototypePattern_classic/RectanglePrototype.cpp
)

target_include_directories(PrototypePatternClassic
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(PrototypePatternClassic PUBLIC cxx_std_23)

add_library(PrototypePatternModern
    src/PrototypePattern_modern/CirclePrototype.cpp
    src/PrototypePattern_modern/RectanglePrototype.cpp
)

target_include_directories(PrototypePatternModern
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(PrototypePatternModern PUBLIC cxx_std_23)

add_executable(PrototypePatternDemo
    src/PrototypePatternDemo.cpp
)

target_link_libraries(PrototypePatternDemo
    PRIVATE
        PrototypePatternClassic
)

add_executable(PrototypePatternModernDemo
    src/PrototypePatternModernDemo.cpp
)

target_link_libraries(PrototypePatternModernDemo
    PRIVATE
        PrototypePatternModern
)
