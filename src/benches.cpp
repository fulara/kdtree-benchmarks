#include "benchmark/benchmark_api.h"

#include "Kdtree3Cgal.h"
#include "kdtree-rust-c-api.h"

#include "RandomGenerator.h"

void Cgal_tree_buildup(benchmark::State& state) {
    RandomGenerator rg;
    rg.reseed();

    std::vector<Vector3> nodes;
    const unsigned count = (const unsigned int) state.range(0);

    for (auto i = 0u; i < count; ++i) {
        nodes.push_back(Vector3(i, rg.random_double(0, count), rg.random_double(0, count), rg.random_double(0, count)));
    }

    while(state.KeepRunning()) {

        Kdtree3Cgal tree;
        tree.insert(nodes);

        //we need to do at least 1 lookup because cgal builds tree lazily.
        auto v = static_cast<Vector3*>(&nodes[0]);
        tree.nearestNeighborSearch(v);
    }
}


void Cgal_tree_lookup(benchmark::State& state) {
    RandomGenerator rg;
    Kdtree3Cgal tree;
    std::vector<Vector3> nodes;

    const unsigned count = (const unsigned int) state.range(0);

    for (auto i = 0u; i < count; ++i) {
        nodes.push_back(Vector3(i, rg.random_double(0, count), rg.random_double(0, count), rg.random_double(0, count)));
    }

    tree.insert(nodes);
    //we need to do this, because cgal tree is a lazy one.
    auto v = static_cast<Vector3*>(&nodes[0]);
    tree.nearestNeighborSearch(v);

    auto i = 0u;
    while(state.KeepRunning()) {

        auto v = static_cast<Vector3*>(&nodes[i]);
        tree.nearestNeighborSearch(v);

        ++i;
        if(i >= count) {
            i = 0;
        }
    }
}

void Rust_tree_buildup(benchmark::State& state) {
    RandomGenerator rg;
    const unsigned count = (const unsigned int) state.range(0);
    rg.reseed();
    std::vector<Point3WithId> nodes;

    for (auto i = 0u; i < count; ++i) {
        nodes.push_back(Point3WithId{(int)i, rg.random_double(0, count), rg.random_double(0, count), rg.random_double(0, count)});
    }

    while(state.KeepRunning()) {

        kdtree_create(nodes.data(), count);
    }
}

void Rust_tree_lookup(benchmark::State& state) {
    RandomGenerator rg;
    std::vector<Point3WithId> nodes;

    const unsigned count = (const unsigned int) state.range(0);

    for (auto i = 0u; i < count; ++i) {
        nodes.push_back(Point3WithId{(int)i, rg.random_double(0, count), rg.random_double(0, count), rg.random_double(0, count)});
    }

    kdtree_create(nodes.data(), count);

    auto i = 0u;
    while(state.KeepRunning()) {

        auto v = &nodes[i];
        kdtree_nearest_search(v);

        ++i;
        if(i >= count) {
            i = 0;
        }
    }
}

BENCHMARK(Cgal_tree_buildup)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Arg(1000000);
BENCHMARK(Cgal_tree_lookup)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Arg(1000000);

BENCHMARK(Rust_tree_buildup)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Arg(1000000);
BENCHMARK(Rust_tree_lookup)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->Arg(1000000);