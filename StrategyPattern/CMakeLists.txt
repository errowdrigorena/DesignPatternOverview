add_library(StrategyPattern
    src/Shapes_strategy/ApiDrawStrategy.cpp
    src/Shapes_strategy/Circle_strategy.cpp
    src/Shapes_strategy/Rectangle_strategy.cpp
    src/Shapes_strategy/Shapes.cpp
    src/Shapes_strategy/StarDrawStrategy.cpp
    src/Shapes_strategy/Triangle_strategy.cpp
)

target_include_directories(StrategyPattern
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(StrategyPattern PUBLIC cxx_std_23)

add_executable(StrategyPatternDemo
    src/ShapesStrategyDemo.cpp
)

target_link_libraries(StrategyPatternDemo
    PRIVATE
        StrategyPattern
)
