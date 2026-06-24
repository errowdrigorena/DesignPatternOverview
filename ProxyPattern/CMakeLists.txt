add_library(ProxyPatternClassic
    src/ProxyPattern_classic/RealService.cpp
    src/ProxyPattern_classic/VirtualProxy.cpp
    src/ProxyPattern_classic/ProtectionProxy.cpp
)

target_include_directories(ProxyPatternClassic
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(ProxyPatternClassic PUBLIC cxx_std_23)

add_executable(ProxyPatternDemo
    src/ProxyPatternDemo.cpp
)

target_link_libraries(ProxyPatternDemo
    PRIVATE
        ProxyPatternClassic
)

add_library(ProxyPatternModern
    src/ProxyPattern_modern/RealService.cpp
    src/ProxyPattern_modern/VirtualProxy.cpp
    src/ProxyPattern_modern/ProtectionProxy.cpp
)

target_include_directories(ProxyPatternModern
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(ProxyPatternModern PUBLIC cxx_std_23)

add_executable(ProxyPatternModernDemo
    src/ProxyPatternModernDemo.cpp
)

target_link_libraries(ProxyPatternModernDemo
    PRIVATE
        ProxyPatternModern
)
