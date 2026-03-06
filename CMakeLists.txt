cmake_minimum_required(VERSION 3.14)

project(linalg)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.12.1
)

FetchContent_Declare(
  benchmark
  GIT_REPOSITORY https://github.com/google/benchmark.git
  GIT_TAG        v1.8.3
)
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
set(BENCHMARK_ENABLE_GTEST_TESTS OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest benchmark)

include_directories(include)

set(SOURCES
    ./include/matrix.hpp
    ./src/matrix.cpp
)

set(TESTSOURCES
    ${SOURCES}
    ./tests/test_matrix.cpp
)

add_executable(linalg)
target_sources(linalg PRIVATE ${SOURCES} ./src/main.cpp)

enable_testing()
add_executable(run_tests)
target_sources(run_tests PRIVATE ${TESTSOURCES})
target_link_libraries(
    run_tests
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(run_tests)

# set(BENCHSOURCES
#     ${SOURCES}
#     ./benchmarks/bench_utils.cpp
#     ./benchmarks/main.cpp
# )
#
# add_executable(run_benchmarks)
# target_sources(run_benchmarks PRIVATE ${BENCHSOURCES})
# target_link_libraries(
#     run_benchmarks
#     benchmark::benchmark_main
# )
