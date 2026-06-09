add_library(SingletonPattern
    src/SingletonPattern_classic/ApplicationLogger.cpp
)

target_include_directories(SingletonPattern
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(SingletonPattern PUBLIC cxx_std_23)

add_library(SingletonPatternModern INTERFACE)

target_include_directories(SingletonPatternModern
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(SingletonPatternModern INTERFACE cxx_std_23)

add_executable(SingletonPatternDemo
    src/SingletonPatternDemo.cpp
)

target_link_libraries(SingletonPatternDemo
    PRIVATE
        SingletonPattern
)

add_executable(SingletonPatternModernDemo
    src/SingletonPatternModernDemo.cpp
)

target_link_libraries(SingletonPatternModernDemo
    PRIVATE
        SingletonPatternModern
)
