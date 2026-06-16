add_library(MementoPatternClassic
    src/MementoPattern_classic/CanvasHistory.cpp
    src/MementoPattern_classic/ShapeCanvas.cpp
)

target_include_directories(MementoPatternClassic
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(MementoPatternClassic PUBLIC cxx_std_23)

add_library(MementoPatternModern
    src/MementoPattern_modern/nested_snapshot/ShapeCanvas.cpp
    src/MementoPattern_modern/persistent/ShapeCanvas.cpp
    src/MementoPattern_modern/value_snapshot/ShapeCanvas.cpp
    src/MementoPattern_modern/vector_history/ShapeCanvas.cpp
)

target_include_directories(MementoPatternModern
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(MementoPatternModern PUBLIC cxx_std_23)
