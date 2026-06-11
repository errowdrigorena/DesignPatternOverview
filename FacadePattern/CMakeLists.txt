add_library(FacadePatternClassic
    src/FacadePattern_classic/Amplifier.cpp
    src/FacadePattern_classic/Projector.cpp
    src/FacadePattern_classic/StreamingPlayer.cpp
    src/FacadePattern_classic/HomeTheaterFacade.cpp
)

target_include_directories(FacadePatternClassic
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(FacadePatternClassic PUBLIC cxx_std_23)

add_executable(FacadePatternDemo
    src/FacadePatternDemo.cpp
)

target_link_libraries(FacadePatternDemo
    PRIVATE
        FacadePatternClassic
)
