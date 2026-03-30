add_executable(run_tests resizeable_array_tests.cpp)

target_link_libraries(run_tests
        PRIVATE
        GTest::gtest
        GTest::gtest_main
)

target_include_directories(run_tests PRIVATE ${googletest_SOURCE_DIR}/googletest/include)

include(GoogleTest)
gtest_discover_tests(run_tests)