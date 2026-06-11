cmake_minimum_required(VERSION 3.16)

project(DesignPatternOverview LANGUAGES CXX)

include(CTest)

add_subdirectory(Shapes)
add_subdirectory(StrategyPattern)
add_subdirectory(ObserverPattern)
add_subdirectory(CommandPattern)
add_subdirectory(SimpleFactoryPseudoPattern)
add_subdirectory(SingletonPattern)
add_subdirectory(VisitorPattern)
add_subdirectory(DecoratorPattern)
add_subdirectory(FacadePattern)

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()
