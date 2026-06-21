add_library(MediatorPatternClassic
    src/MediatorPattern_classic/Component.cpp
    src/MediatorPattern_classic/NumberField.cpp
    src/MediatorPattern_classic/CheckBox.cpp
    src/MediatorPattern_classic/RectanglePreview.cpp
    src/MediatorPattern_classic/RectangleDialog.cpp
)

target_include_directories(MediatorPatternClassic
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(MediatorPatternClassic PUBLIC cxx_std_23)

add_library(MediatorPatternModern
    src/MediatorPattern_modern/NumberField.cpp
    src/MediatorPattern_modern/CheckBox.cpp
    src/MediatorPattern_modern/RectanglePreview.cpp
    src/MediatorPattern_modern/RectangleDialog.cpp
)

target_include_directories(MediatorPatternModern
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(MediatorPatternModern PUBLIC cxx_std_23)

add_executable(MediatorPatternDemo
    src/MediatorPatternDemo.cpp
)

target_link_libraries(MediatorPatternDemo
    PRIVATE
        MediatorPatternClassic
)

add_executable(MediatorPatternModernDemo
    src/MediatorPatternModernDemo.cpp
)

target_link_libraries(MediatorPatternModernDemo
    PRIVATE
        MediatorPatternModern
)
