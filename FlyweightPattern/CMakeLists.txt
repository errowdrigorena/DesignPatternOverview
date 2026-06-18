add_library(FlyweightPatternClassic
    src/FlyweightPattern_classic/IconCatalog.cpp
    src/FlyweightPattern_classic/MapMarker.cpp
    src/FlyweightPattern_classic/MarkerIcon.cpp
)

target_include_directories(FlyweightPatternClassic
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(FlyweightPatternClassic PUBLIC cxx_std_23)

add_library(FlyweightPatternModern INTERFACE)

target_include_directories(FlyweightPatternModern
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(FlyweightPatternModern INTERFACE cxx_std_23)

add_executable(FlyweightPatternDemo
    src/FlyweightPatternDemo.cpp
)

target_link_libraries(FlyweightPatternDemo
    PRIVATE
        FlyweightPatternClassic
)

add_executable(FlyweightPatternModernDemo
    src/FlyweightPatternModernDemo.cpp
)

target_link_libraries(FlyweightPatternModernDemo
    PRIVATE
        FlyweightPatternModern
)

add_executable(FlyweightPatternModernByKindDemo
    src/FlyweightPatternModernByKindDemo.cpp
)

target_link_libraries(FlyweightPatternModernByKindDemo
    PRIVATE
        FlyweightPatternModern
)

add_executable(FlyweightPatternModernHandlePoolDemo
    src/FlyweightPatternModernHandlePoolDemo.cpp
)

target_link_libraries(FlyweightPatternModernHandlePoolDemo
    PRIVATE
        FlyweightPatternModern
)

add_executable(FlyweightPatternModernStaticTableDemo
    src/FlyweightPatternModernStaticTableDemo.cpp
)

target_link_libraries(FlyweightPatternModernStaticTableDemo
    PRIVATE
        FlyweightPatternModern
)
