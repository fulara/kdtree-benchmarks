cmake_minimum_required(VERSION 3.0)

project(kdtree_benchmarks)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wno-deprecated-declarations -O3 -Wall ")

include_directories(include)

set(SOURCE_FILES src/main.cpp)

add_executable(kdtree_benchmarks ${SOURCE_FILES} ${TEST_SOURCE_FILES})
