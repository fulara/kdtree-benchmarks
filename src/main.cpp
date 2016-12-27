#include "benchmark/benchmark_api.h"


void BM_testing(benchmark::State& state) {
    std::vector<int> s;
    s.reserve(5000);
}
BENCHMARK(BM_testing);

BENCHMARK_MAIN()