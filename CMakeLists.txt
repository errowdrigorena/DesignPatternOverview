cmake_minimum_required(VERSION 3.25)

find_program(GXX_15 g++-15 REQUIRED)
find_program(GCC_15 gcc-15 REQUIRED)
set(CMAKE_C_COMPILER ${GCC_15} CACHE FILEPATH "C compiler" FORCE)
set(CMAKE_CXX_COMPILER ${GXX_15} CACHE FILEPATH "C++ compiler" FORCE)

project(DesignPatternOverview LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(ENABLE_COVERAGE "Build with coverage instrumentation" OFF)

if(ENABLE_COVERAGE)
    if(NOT CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        message(FATAL_ERROR "ENABLE_COVERAGE requires GCC or Clang")
    endif()

    add_compile_options(-O0 -g --coverage)
    add_link_options(--coverage)
endif()

include(CTest)

add_subdirectory(Shapes)
add_subdirectory(StrategyPattern)
add_subdirectory(ObserverPattern)
add_subdirectory(CommandPattern)
add_subdirectory(AdapterPattern)
add_subdirectory(SimpleFactoryPseudoPattern)
add_subdirectory(FactoryMethodPattern)
add_subdirectory(SingletonPattern)
add_subdirectory(VisitorPattern)
add_subdirectory(DecoratorPattern)
add_subdirectory(FacadePattern)
add_subdirectory(FlyweightPattern)
add_subdirectory(MementoPattern)
add_subdirectory(TemplateMethodPattern)
add_subdirectory(PrototypePattern)
add_subdirectory(InterpreterPattern)

if(BUILD_TESTING)
    add_subdirectory(tests)

    if(ENABLE_COVERAGE)
        find_program(GCOV_COMMAND gcov REQUIRED)
        set(COVERAGE_COMMAND "${GCOV_COMMAND}" CACHE FILEPATH "Coverage tool")

        set(COVERAGE_TEST_TARGETS
            CommandPatternClassicTests
            CommandPatternModernTests
            AdapterPatternCommonTests
            AdapterPatternClassicTests
            AdapterPatternModernTests
            DecoratorPatternClassicTests
            DecoratorPatternModernTests
            FacadePatternClassicTests
            FactoryMethodPatternClassicTests
            FactoryMethodPatternModernTests
            FactoryMethodPatternSimpleFactoryTests
            FlyweightPatternClassicTests
            FlyweightPatternModernByKindTests
            FlyweightPatternModernHandlePoolTests
            FlyweightPatternModernStaticTableTests
            FlyweightPatternModernTests
            InterpreterPatternClassicTests
            InterpreterPatternModernBisonRulesTests
            InterpreterPatternModernVariantAstTests
            MementoPatternClassicTests
            MementoPatternModernNestedSnapshotTests
            MementoPatternModernPersistentTests
            MementoPatternModernValueSnapshotTests
            MementoPatternModernVectorHistoryTests
            ObserverPatternClassicTests
            ObserverPatternModernTests
            PrototypePatternClassicTests
            PrototypePatternModernTests
            SimpleFactoryPseudoPatternRuntimeTests
            SimpleFactoryPseudoPatternTemplateTests
            ShapesModernTests
            ShapesTraditionalTests
            SingletonPatternTests
            StrategyPatternClassicTests
            StrategyPatternFunctionTests
            TemplateMethodPatternCallableTests
            TemplateMethodPatternClassicTests
            TemplateMethodPatternConceptsTests
            TemplateMethodPatternCrtpTests
            TemplateMethodPatternDeducingThisTests
            VisitorPatternClassicTests
            VisitorPatternModernTests
        )

        add_custom_target(coverage
            DEPENDS ${COVERAGE_TEST_TARGETS}
            COMMAND ${CMAKE_CTEST_COMMAND} --test-dir ${CMAKE_BINARY_DIR} --output-on-failure
            COMMAND ${CMAKE_CTEST_COMMAND} -T Coverage --test-dir ${CMAKE_BINARY_DIR}
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMENT "Running tests and collecting coverage"
            VERBATIM
        )
    endif()
endif()
