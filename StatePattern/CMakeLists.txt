find_package(Boost REQUIRED CONFIG)

# ── Common include path shared by all state-pattern variants ──────────────────
set(STATE_PATTERN_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# ── Classic GoF ───────────────────────────────────────────────────────────────

add_library(StatePatternClassic
    src/StatePattern_classic/CoffeeMachine.cpp
    src/StatePattern_classic/States.cpp
)
target_include_directories(StatePatternClassic PUBLIC ${STATE_PATTERN_INCLUDE})
target_compile_features(StatePatternClassic PUBLIC cxx_std_23)

add_executable(StatePatternClassicDemo src/StatePatternClassicDemo.cpp)
target_link_libraries(StatePatternClassicDemo PRIVATE StatePatternClassic)

# ── Classic Generic ───────────────────────────────────────────────────────────

add_library(StatePatternClassicGeneric
    src/StatePattern_classic_generic/CoffeeMachine.cpp
)
target_include_directories(StatePatternClassicGeneric PUBLIC ${STATE_PATTERN_INCLUDE})
target_compile_features(StatePatternClassicGeneric PUBLIC cxx_std_23)

add_executable(StatePatternClassicGenericDemo src/StatePatternClassicGenericDemo.cpp)
target_link_libraries(StatePatternClassicGenericDemo PRIVATE StatePatternClassicGeneric)

# ── std::variant ──────────────────────────────────────────────────────────────
# Header-only — no compiled library needed.

add_executable(StatePatternVariantDemo src/StatePatternVariantDemo.cpp)
target_include_directories(StatePatternVariantDemo PRIVATE ${STATE_PATTERN_INCLUDE})
target_compile_features(StatePatternVariantDemo PRIVATE cxx_std_23)

# ── Table-based (TFiniteStateMachine) ────────────────────────────────────────

add_library(StatePatternTable
    src/StatePattern_table/CoffeeMachine.cpp
)
target_include_directories(StatePatternTable PUBLIC ${STATE_PATTERN_INCLUDE})
target_compile_features(StatePatternTable PUBLIC cxx_std_23)

add_executable(StatePatternTableDemo src/StatePatternTableDemo.cpp)
target_link_libraries(StatePatternTableDemo PRIVATE StatePatternTable)

# ── Boost-Inspired compile-time table ────────────────────────────────────────
# Header-only — no compiled library needed.

add_executable(StatePatternBoostInspiredDemo src/StatePatternBoostInspiredDemo.cpp)
target_include_directories(StatePatternBoostInspiredDemo PRIVATE ${STATE_PATTERN_INCLUDE})
target_compile_features(StatePatternBoostInspiredDemo PRIVATE cxx_std_23)

# ── Boost.MSM ─────────────────────────────────────────────────────────────────
# Header-only Boost library — link the Boost interface target for include paths.

add_executable(StatePatternBoostDemo src/StatePatternBoostDemo.cpp)
target_include_directories(StatePatternBoostDemo PRIVATE ${STATE_PATTERN_INCLUDE})
target_link_libraries(StatePatternBoostDemo PRIVATE Boost::boost)
target_compile_features(StatePatternBoostDemo PRIVATE cxx_std_23)
