add_library(CommandPatternClassic
    src/CommandPattern_classic/CommandHistory.cpp
    src/CommandPattern_classic/DoBoringCommand.cpp
    src/CommandPattern_classic/DoCoolCommand.cpp
)

target_include_directories(CommandPatternClassic
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(CommandPatternClassic PUBLIC cxx_std_23)

add_library(CommandPatternModern
    src/CommandPattern_modern/CommandHistory.cpp
)

target_include_directories(CommandPatternModern
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(CommandPatternModern PUBLIC cxx_std_23)

add_executable(CommandPatternDemo
    src/CommandPatternDemo.cpp
)

target_link_libraries(CommandPatternDemo
    PRIVATE
        CommandPatternClassic
)

add_executable(CommandPatternModernDemo
    src/CommandPatternModernDemo.cpp
)

target_link_libraries(CommandPatternModernDemo
    PRIVATE
        CommandPatternModern
)
