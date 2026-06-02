add_library(VisitorPatternClassic
    src/VisitorPattern_classic/AreaVisitor.cpp
    src/VisitorPattern_classic/Circle.cpp
    src/VisitorPattern_classic/DrawVisitor.cpp
    src/VisitorPattern_classic/Rectangle.cpp
    src/VisitorPattern_classic/Triangle.cpp
)

target_include_directories(VisitorPatternClassic
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(VisitorPatternClassic PUBLIC cxx_std_23)

add_library(VisitorPatternModern INTERFACE)

target_include_directories(VisitorPatternModern
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(VisitorPatternModern INTERFACE cxx_std_23)

add_executable(VisitorPatternDemo
    src/VisitorPatternDemo.cpp
)

target_link_libraries(VisitorPatternDemo
    PRIVATE
        VisitorPatternClassic
)

add_executable(VisitorPatternModernDemo
    src/VisitorPatternModernDemo.cpp
)

target_link_libraries(VisitorPatternModernDemo
    PRIVATE
        VisitorPatternModern
)
