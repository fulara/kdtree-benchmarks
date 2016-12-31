#include "gtest/gtest.h"

#include "Kdtree3Cgal.h"
#include "kdtree-rust-c-api.h"
#include "RandomGenerator.h"


struct KdtreeTests : ::testing::Test {
};

TEST(KdtreeTests, RustAndCgalTreesGiveTheSameResults) {
    RandomGenerator rg;
    rg.reseed();

    std::vector<Vector3> cgalNodes;
    std::vector<Point3WithId> rustNodes;
    const int count = 2000000;

    for (auto i = 0u; i < count; ++i) {
        auto x = rg.random_double(0, count);
        auto y = rg.random_double(0, count);
        auto z = rg.random_double(0, count);
        cgalNodes.push_back(Vector3((int)i, x,y,z));
        rustNodes.push_back(Point3WithId{reinterpret_cast<void*>(i), x,y,z});
    }

    Kdtree3Cgal kdtree3Cgal;
    kdtree3Cgal.insert(cgalNodes);

    kdtree_create(rustNodes.data(), rustNodes.size());

    for(auto i = 0u ; i < 1000000u ; ++i) {
        auto x = rg.random_double(0, count);
        auto y = rg.random_double(0, count);
        auto z = rg.random_double(0, count);

        Vector3 v(0, x,y,z);
        Point3WithId p{0,x,y,z};
        auto found_by_cgal = kdtree3Cgal.nearestNeighborSearch(&v);
        auto found_by_kdtree = kdtree_nearest_search(&p);

        ASSERT_EQ((size_t)found_by_cgal->id, (size_t)found_by_kdtree.pointer);
    }
}

TEST(KdtreeTests, testThatAllExportedFunctionsWork) {
    std::vector<Point3WithId> rustNodes;
    rustNodes.push_back(Point3WithId{(void*)0, 0,0,0});

    kdtree_create(rustNodes.data(), rustNodes.size());

    auto p = Point3WithId{(void*)0, 1,0,0};
    kdtree_insert_node(&p);
    p = Point3WithId{(void*)0, 5,0,0};
    kdtree_insert_node(&p);

    p = Point3WithId{(void*)0,3,0,0};
    ASSERT_DOUBLE_EQ(4, kdtree_distance_squared_to_nearest(&p));
    p = Point3WithId{(void*)0,4,0,0};
    ASSERT_DOUBLE_EQ(1, kdtree_distance_squared_to_nearest(&p));
    ASSERT_FALSE(kdtree_has_neighbor_in_range(&p, 0.5));
    ASSERT_TRUE(kdtree_has_neighbor_in_range(&p, 1.1));
}