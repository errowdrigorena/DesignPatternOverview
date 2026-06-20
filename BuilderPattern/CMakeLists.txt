add_library(BuilderPatternCommon
    src/BuilderPattern_common/Rectangle.cpp
)

target_include_directories(BuilderPatternCommon
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(BuilderPatternCommon PUBLIC cxx_std_23)

add_library(BuilderPatternClassic
    src/BuilderPattern_classic/RectangleBuilder.cpp
    src/BuilderPattern_classic/RectangleDirector.cpp
)

target_include_directories(BuilderPatternClassic
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(BuilderPatternClassic PUBLIC cxx_std_23)

target_link_libraries(BuilderPatternClassic
    PUBLIC
        BuilderPatternCommon
)

add_library(BuilderPatternModern
    src/BuilderPattern_modern/RectangleBuilder.cpp
)

target_include_directories(BuilderPatternModern
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(BuilderPatternModern PUBLIC cxx_std_23)

target_link_libraries(BuilderPatternModern
    PUBLIC
        BuilderPatternCommon
)

add_executable(BuilderPatternDemo
    src/BuilderPatternDemo.cpp
)

target_link_libraries(BuilderPatternDemo
    PRIVATE
        BuilderPatternClassic
)

add_executable(BuilderPatternModernDemo
    src/BuilderPatternModernDemo.cpp
)

target_link_libraries(BuilderPatternModernDemo
    PRIVATE
        BuilderPatternModern
)
