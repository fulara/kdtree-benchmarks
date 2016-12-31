#pragma once

extern "C" {

struct Point3WithId {
    void* pointer;
    double vals[3];
};

void kdtree_create(Point3WithId* points, size_t len);
Point3WithId kdtree_nearest_search(Point3WithId* for_node);
bool kdtree_has_neighbor_in_range(Point3WithId* for_node, double range);
double kdtree_distance_squared_to_nearest(Point3WithId* for_node);
double kdtree_insert_node(Point3WithId* for_node);
}
