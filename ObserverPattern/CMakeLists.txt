add_library(ObserverPattern
    src/ConsoleObserver.cpp
    src/Subject.cpp
)

target_include_directories(ObserverPattern
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(ObserverPattern PUBLIC cxx_std_23)

add_executable(ObserverPatternDemo
    src/ObserverPatternDemo.cpp
)

target_link_libraries(ObserverPatternDemo
    PRIVATE
        ObserverPattern
)
