#pragma once

#include <memory>
#include <vector>

#include <boost/noncopyable.hpp>

struct Vector3 {
    Vector3()
            : id(0), x(0), y(0), z(0)
    {
    }

    Vector3(int id, double x, double y, double z) : id(id), x(x), y(y), z(z)
    {
    }
    
    int id;
    double x;
    double y;
    double z;
};
class Kdtree3CgalImpl;

class Kdtree3Cgal : boost::noncopyable
{
public:
    Kdtree3Cgal();
    ~Kdtree3Cgal();

    Kdtree3Cgal(const std::vector<Vector3 *> &nodes);
    void addNode(Vector3 *node);
    void insert(const std::vector<Vector3 *> &nodes);
    void insert(const std::vector<Vector3> &nodes);

    Vector3 *nearestNeighborSearch(Vector3 *query) const;
    double distanceToClosestNeighbor(Vector3 *query) const;
    bool hasNeighborInRange(Vector3 *point, double range) const;
private:
    std::unique_ptr<Kdtree3CgalImpl> impl;
};