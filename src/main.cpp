#include "benchmark/benchmark_api.h"

#include "gtest/gtest.h"


int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    auto gtest_value = RUN_ALL_TESTS();

    benchmark::Initialize(&argc, argv);
    benchmark::RunSpecifiedBenchmarks();

    return gtest_value;
}