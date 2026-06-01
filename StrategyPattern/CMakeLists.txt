add_library(StrategyPattern
    src/Shapes_strategy_classic/ApiDrawStrategy.cpp
    src/Shapes_strategy_classic/Circle_strategy.cpp
    src/Shapes_strategy_classic/Rectangle_strategy.cpp
    src/Shapes_strategy_classic/Shapes.cpp
    src/Shapes_strategy_classic/StarDrawStrategy.cpp
    src/Shapes_strategy_classic/Triangle_strategy.cpp
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
