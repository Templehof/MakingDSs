cmake_minimum_required(VERSION 4.2)
project(MakingDSs)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

FetchContent_MakeAvailable(googletest)

include_directories(include)

enable_testing()
add_subdirectory(tests)

add_executable(MakingDSs main.cpp
        simple_data_structures/resizeable_array/ResizeableArray.h
        concurrency_safe_data_structures/NaiveConcurrentResizeableArray.h
)
