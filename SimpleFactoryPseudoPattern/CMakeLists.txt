add_library(SimpleFactoryPseudoPatternSwitch
    src/SimpleFactoryPseudoPattern_switch/ShapeFactory.cpp
)

target_include_directories(SimpleFactoryPseudoPatternSwitch
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(SimpleFactoryPseudoPatternSwitch PUBLIC cxx_std_23)

target_link_libraries(SimpleFactoryPseudoPatternSwitch
    PUBLIC
        Shapes_traditional
)

add_library(SimpleFactoryPseudoPatternMap
    src/SimpleFactoryPseudoPattern_map/ShapeFactory.cpp
)

target_include_directories(SimpleFactoryPseudoPatternMap
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(SimpleFactoryPseudoPatternMap PUBLIC cxx_std_23)

target_link_libraries(SimpleFactoryPseudoPatternMap
    PUBLIC
        Shapes_traditional
)

add_library(SimpleFactoryPseudoPatternTemplate INTERFACE)

target_include_directories(SimpleFactoryPseudoPatternTemplate
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(SimpleFactoryPseudoPatternTemplate INTERFACE cxx_std_23)

target_link_libraries(SimpleFactoryPseudoPatternTemplate
    INTERFACE
        Shapes_traditional
)

add_executable(SimpleFactoryPseudoPatternSwitchDemo
    src/SimpleFactoryPseudoPatternSwitchDemo.cpp
)

target_link_libraries(SimpleFactoryPseudoPatternSwitchDemo
    PRIVATE
        SimpleFactoryPseudoPatternSwitch
)

add_executable(SimpleFactoryPseudoPatternMapDemo
    src/SimpleFactoryPseudoPatternMapDemo.cpp
)

target_link_libraries(SimpleFactoryPseudoPatternMapDemo
    PRIVATE
        SimpleFactoryPseudoPatternMap
)

add_executable(SimpleFactoryPseudoPatternTemplateDemo
    src/SimpleFactoryPseudoPatternTemplateDemo.cpp
)

target_link_libraries(SimpleFactoryPseudoPatternTemplateDemo
    PRIVATE
        SimpleFactoryPseudoPatternTemplate
)
