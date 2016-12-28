#pragma once

extern "C" {

struct Point3WithId {
    int num;
    double vals[3];
};

void kdtree_create(Point3WithId* points, size_t len);
Point3WithId kdtree_nearest_search(Point3WithId* for_node);

}
