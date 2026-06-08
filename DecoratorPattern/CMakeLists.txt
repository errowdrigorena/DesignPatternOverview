add_library(DecoratorPatternClassic
    src/DecoratorPattern_classic/ConcreteComponent.cpp
    src/DecoratorPattern_classic/Decorator.cpp
    src/DecoratorPattern_classic/ConcreteDecoratorA.cpp
    src/DecoratorPattern_classic/ConcreteDecoratorB.cpp
    src/DecoratorPattern_classic/ConcreteDecoratorC.cpp
)

target_include_directories(DecoratorPatternClassic
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(DecoratorPatternClassic PUBLIC cxx_std_23)

add_executable(DecoratorPatternDemo
    src/DecoratorPatternDemo.cpp
)

target_link_libraries(DecoratorPatternDemo
    PRIVATE
        DecoratorPatternClassic
)
