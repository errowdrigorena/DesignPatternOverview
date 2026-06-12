add_library(PrototypePatternClassic
    PrototypePattern_classic/Prototype.cpp
)

target_include_directories(PrototypePatternClassic
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_features(PrototypePatternClassic PUBLIC cxx_std_23)

add_library(PrototypePatternModern INTERFACE)

target_include_directories(PrototypePatternModern
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_features(PrototypePatternModern INTERFACE cxx_std_23)

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
