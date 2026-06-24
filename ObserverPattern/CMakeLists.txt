add_library(ObserverPattern
    src/ObserverPattern_classic/ConsoleObserver.cpp
    src/ObserverPattern_classic/Subject.cpp
)

target_include_directories(ObserverPattern
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(ObserverPattern PUBLIC cxx_std_23)

add_library(ObserverPatternModern INTERFACE)

target_include_directories(ObserverPatternModern
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(ObserverPatternModern INTERFACE cxx_std_23)

add_executable(ObserverPatternDemo
    src/ObserverPatternDemo.cpp
)

target_link_libraries(ObserverPatternDemo
    PRIVATE
        ObserverPattern
)

add_executable(ObserverPatternModernDemo
    src/ObserverPatternModernDemo.cpp
)

target_link_libraries(ObserverPatternModernDemo
    PRIVATE
        ObserverPatternModern
)

add_executable(ObserverPatternFilteredDemo
    src/ObserverPatternFilteredDemo.cpp
)

target_link_libraries(ObserverPatternFilteredDemo
    PRIVATE
        ObserverPatternModern
)

add_library(ObserverPatternBoost INTERFACE)

target_include_directories(ObserverPatternBoost
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(ObserverPatternBoost INTERFACE cxx_std_23)

target_link_libraries(ObserverPatternBoost
    INTERFACE
        boost::boost
)

add_executable(ObserverPatternBoostDemo
    src/ObserverPatternBoostDemo.cpp
)

target_link_libraries(ObserverPatternBoostDemo
    PRIVATE
        ObserverPatternBoost
)
