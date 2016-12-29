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
        rustNodes.push_back(Point3WithId{(int)i, x,y,z});
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

        ASSERT_EQ(found_by_cgal->id, found_by_kdtree.num);
    }
}