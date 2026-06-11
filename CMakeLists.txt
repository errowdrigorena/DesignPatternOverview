cmake_minimum_required(VERSION 3.25)

find_program(GXX_15 g++-15 REQUIRED)
set(CMAKE_CXX_COMPILER ${GXX_15} CACHE FILEPATH "C++ compiler" FORCE)

project(DesignPatternOverview LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

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
add_subdirectory(TemplateMethodPattern)

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()
