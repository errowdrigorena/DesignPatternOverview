set(STATE_PATTERN_INCLUDE ${CMAKE_SOURCE_DIR}/StatePattern/include)
set(FSM_INCLUDE           ${CMAKE_SOURCE_DIR}/FSM)

# ── Classic GoF ───────────────────────────────────────────────────────────────

add_executable(StatePatternClassicTests StatePatternClassicTests.cpp)
target_link_libraries(StatePatternClassicTests PRIVATE
    StatePatternClassic GTest::gmock GTest::gtest_main)
target_compile_features(StatePatternClassicTests PRIVATE cxx_std_23)
gtest_discover_tests(StatePatternClassicTests)

# ── Classic Generic ───────────────────────────────────────────────────────────

add_executable(StatePatternClassicGenericTests StatePatternClassicGenericTests.cpp)
target_link_libraries(StatePatternClassicGenericTests PRIVATE
    StatePatternClassicGeneric GTest::gmock GTest::gtest_main)
target_compile_features(StatePatternClassicGenericTests PRIVATE cxx_std_23)
gtest_discover_tests(StatePatternClassicGenericTests)

# ── std::variant ──────────────────────────────────────────────────────────────

add_executable(StatePatternVariantTests StatePatternVariantTests.cpp)
target_include_directories(StatePatternVariantTests PRIVATE ${STATE_PATTERN_INCLUDE})
target_link_libraries(StatePatternVariantTests PRIVATE GTest::gmock GTest::gtest_main)
target_compile_features(StatePatternVariantTests PRIVATE cxx_std_23)
gtest_discover_tests(StatePatternVariantTests)

# ── Table-based ───────────────────────────────────────────────────────────────

add_executable(StatePatternTableTests StatePatternTableTests.cpp)
target_link_libraries(StatePatternTableTests PRIVATE
    StatePatternTable GTest::gmock GTest::gtest_main)
target_compile_features(StatePatternTableTests PRIVATE cxx_std_23)
gtest_discover_tests(StatePatternTableTests)

# ── Boost-Inspired ────────────────────────────────────────────────────────────

add_executable(StatePatternBoostInspiredTests StatePatternBoostInspiredTests.cpp)
target_include_directories(StatePatternBoostInspiredTests PRIVATE ${STATE_PATTERN_INCLUDE})
target_link_libraries(StatePatternBoostInspiredTests PRIVATE GTest::gmock GTest::gtest_main)
target_compile_features(StatePatternBoostInspiredTests PRIVATE cxx_std_23)
gtest_discover_tests(StatePatternBoostInspiredTests)

# ── Boost.MSM ─────────────────────────────────────────────────────────────────

find_package(Boost REQUIRED CONFIG)

add_executable(StatePatternBoostTests StatePatternBoostTests.cpp)
target_include_directories(StatePatternBoostTests PRIVATE ${STATE_PATTERN_INCLUDE})
target_link_libraries(StatePatternBoostTests PRIVATE
    Boost::boost GTest::gmock GTest::gtest_main)
target_compile_features(StatePatternBoostTests PRIVATE cxx_std_23)
gtest_discover_tests(StatePatternBoostTests)
