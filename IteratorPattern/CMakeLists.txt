add_library(IteratorPatternClassic
    src/IteratorPattern_classic/ShapeCollection.cpp
    src/IteratorPattern_classic/ShapeCollectionIterator.cpp
)

target_include_directories(IteratorPatternClassic
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(IteratorPatternClassic PUBLIC cxx_std_23)

target_link_libraries(IteratorPatternClassic
    PUBLIC
        Shapes_traditional
)

add_executable(IteratorPatternDemo
    src/IteratorPatternDemo.cpp
)

target_link_libraries(IteratorPatternDemo
    PRIVATE
        IteratorPatternClassic
)

add_library(IteratorPatternModernIterators
    src/IteratorPattern_modern/iterators/ShapeCollection.cpp
)

target_include_directories(IteratorPatternModernIterators
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(IteratorPatternModernIterators PUBLIC cxx_std_23)

target_link_libraries(IteratorPatternModernIterators
    PUBLIC
        Shapes_traditional
)

add_library(IteratorPatternModernRanges INTERFACE)

target_include_directories(IteratorPatternModernRanges
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(IteratorPatternModernRanges INTERFACE cxx_std_23)

target_link_libraries(IteratorPatternModernRanges
    INTERFACE
        Shapes_traditional
)

add_executable(IteratorPatternModernIteratorsDemo
    src/IteratorPatternModernIteratorsDemo.cpp
)

target_link_libraries(IteratorPatternModernIteratorsDemo
    PRIVATE
        IteratorPatternModernIterators
)

add_executable(IteratorPatternModernRangesDemo
    src/IteratorPatternModernRangesDemo.cpp
)

target_link_libraries(IteratorPatternModernRangesDemo
    PRIVATE
        IteratorPatternModernRanges
)

add_library(IteratorPatternBoost
    src/IteratorPattern_boost/ShapeCollection.cpp
)

target_include_directories(IteratorPatternBoost
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(IteratorPatternBoost PUBLIC cxx_std_23)

target_link_libraries(IteratorPatternBoost
    PUBLIC
        boost::boost
        Shapes_traditional
)

add_executable(IteratorPatternBoostDemo
    src/IteratorPatternBoostDemo.cpp
)

target_link_libraries(IteratorPatternBoostDemo
    PRIVATE
        IteratorPatternBoost
)
