add_library(StrategyPattern
    src/Shapes_strategy_classic/ApiDrawStrategy.cpp
    src/Shapes_strategy_classic/Circle_strategy.cpp
    src/Shapes_strategy_classic/Rectangle_strategy.cpp
    src/Shapes_strategy_classic/Shape.cpp
    src/Shapes_strategy_classic/StarDrawStrategy.cpp
    src/Shapes_strategy_classic/Triangle_strategy.cpp
)

target_include_directories(StrategyPattern
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(StrategyPattern PUBLIC cxx_std_23)

add_library(StrategyPatternFunction
    src/Shapes_strategy_function/Circle.cpp
    src/Shapes_strategy_function/DrawStrategies.cpp
    src/Shapes_strategy_function/Rectangle.cpp
    src/Shapes_strategy_function/Triangle.cpp
)

target_include_directories(StrategyPatternFunction
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(StrategyPatternFunction PUBLIC cxx_std_23)

add_executable(StrategyPatternDemo
    src/ShapesStrategyDemo.cpp
)

target_link_libraries(StrategyPatternDemo
    PRIVATE
        StrategyPattern
)

add_executable(StrategyPatternFunctionDemo
    src/ShapesStrategyFunctionDemo.cpp
)

target_link_libraries(StrategyPatternFunctionDemo
    PRIVATE
        StrategyPatternFunction
)
