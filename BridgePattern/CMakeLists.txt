add_library(BridgePatternClassic
    src/BridgePattern_classic/Shape.cpp
    src/BridgePattern_classic/RectangleShape.cpp
    src/BridgePattern_classic/TriangleShape.cpp
    src/BridgePattern_classic/ConsoleShapeRenderer.cpp
    src/BridgePattern_classic/SvgShapeRenderer.cpp
)

target_include_directories(BridgePatternClassic
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(BridgePatternClassic PUBLIC cxx_std_23)

add_library(BridgePatternModern
    src/BridgePattern_modern/Shape.cpp
    src/BridgePattern_modern/Renderers.cpp
)

target_include_directories(BridgePatternModern
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(BridgePatternModern PUBLIC cxx_std_23)

add_executable(BridgePatternDemo
    src/BridgePatternDemo.cpp
)

target_link_libraries(BridgePatternDemo
    PRIVATE
        BridgePatternClassic
)

add_executable(BridgePatternModernDemo
    src/BridgePatternModernDemo.cpp
)

target_link_libraries(BridgePatternModernDemo
    PRIVATE
        BridgePatternModern
)
