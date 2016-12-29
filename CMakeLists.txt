cmake_minimum_required(VERSION 3.0)

project(kdtree_benchmarks)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wno-deprecated-declarations -O3 -Wall -frounding-math ")

include_directories(deps/include/libkdtree_rust_c_api)

set(SOURCE_FILES src/main.cpp src/Kdtree3Cgal.cpp src/Kdtree3Cgal.h src/RandomGenerator.h src/integration_tests.cpp src/benches.cpp)
link_directories(deps/libs/)

add_executable(kdtree_benchmarks ${SOURCE_FILES} ${TEST_SOURCE_FILES})
target_link_libraries(kdtree_benchmarks kdtree_rust_c_api ${CONAN_LIBS} boost_system CGAL pthread)
