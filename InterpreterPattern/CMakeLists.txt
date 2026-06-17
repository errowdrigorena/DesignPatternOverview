add_library(InterpreterPatternClassic
    src/InterpreterPattern_classic/Expressions.cpp
)

target_include_directories(InterpreterPatternClassic
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(InterpreterPatternClassic PUBLIC cxx_std_23)

add_executable(InterpreterPatternDemo
    src/InterpreterPatternDemo.cpp
)

target_link_libraries(InterpreterPatternDemo
    PRIVATE
        InterpreterPatternClassic
)
