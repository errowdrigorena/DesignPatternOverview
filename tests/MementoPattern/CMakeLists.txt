add_executable(MementoPatternClassicTests
    MementoPatternClassicTests.cpp
)

target_link_libraries(MementoPatternClassicTests
    PRIVATE
        MementoPatternClassic
        GTest::gmock
        GTest::gtest_main
)

target_compile_features(MementoPatternClassicTests PRIVATE cxx_std_23)

gtest_discover_tests(MementoPatternClassicTests)

add_executable(MementoPatternModernValueSnapshotTests
    MementoPatternModernValueSnapshotTests.cpp
)

target_link_libraries(MementoPatternModernValueSnapshotTests
    PRIVATE
        MementoPatternModern
        GTest::gmock
        GTest::gtest_main
)

target_compile_features(MementoPatternModernValueSnapshotTests PRIVATE cxx_std_23)

gtest_discover_tests(MementoPatternModernValueSnapshotTests)

add_executable(MementoPatternModernNestedSnapshotTests
    MementoPatternModernNestedSnapshotTests.cpp
)

target_link_libraries(MementoPatternModernNestedSnapshotTests
    PRIVATE
        MementoPatternModern
        GTest::gmock
        GTest::gtest_main
)

target_compile_features(MementoPatternModernNestedSnapshotTests PRIVATE cxx_std_23)

gtest_discover_tests(MementoPatternModernNestedSnapshotTests)

add_executable(MementoPatternModernVectorHistoryTests
    MementoPatternModernVectorHistoryTests.cpp
)

target_link_libraries(MementoPatternModernVectorHistoryTests
    PRIVATE
        MementoPatternModern
        GTest::gmock
        GTest::gtest_main
)

target_compile_features(MementoPatternModernVectorHistoryTests PRIVATE cxx_std_23)

gtest_discover_tests(MementoPatternModernVectorHistoryTests)

add_executable(MementoPatternModernPersistentTests
    MementoPatternModernPersistentTests.cpp
)

target_link_libraries(MementoPatternModernPersistentTests
    PRIVATE
        MementoPatternModern
        GTest::gmock
        GTest::gtest_main
)

target_compile_features(MementoPatternModernPersistentTests PRIVATE cxx_std_23)

gtest_discover_tests(MementoPatternModernPersistentTests)
