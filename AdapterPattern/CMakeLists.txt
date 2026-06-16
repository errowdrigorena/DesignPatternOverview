add_library(AdapterPatternCommon
    src/AdapterPattern_common/LegacyThermometerCApi.c
)

target_include_directories(AdapterPatternCommon
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)


add_library(AdapterPatternClassic
    src/AdapterPattern_classic/ThermometerAdapter.cpp
)

target_include_directories(AdapterPatternClassic
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(AdapterPatternClassic PUBLIC cxx_std_23)

target_link_libraries(AdapterPatternClassic
    PUBLIC
        AdapterPatternCommon
)

add_library(AdapterPatternModern
    src/AdapterPattern_modern/SensorAdapters.cpp
)

target_include_directories(AdapterPatternModern
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(AdapterPatternModern PUBLIC cxx_std_23)

target_link_libraries(AdapterPatternModern
    PUBLIC
        AdapterPatternCommon
)
