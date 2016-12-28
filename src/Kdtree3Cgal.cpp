#include "Kdtree3Cgal.h"

#include <CGAL/Search_traits.h>
#include <CGAL/point_generators_3.h>
#include <CGAL/Orthogonal_k_neighbor_search.h>
#include <CGAL/Fuzzy_sphere.h>
#include <CGAL/Dimension.h>

struct TreePoint3
{
    double vec[3];
    Vector3 *correspondingPoint;

    TreePoint3()
    {
    }

    TreePoint3(Vector3 *point)
    {
        vec[0] = point->x;
        vec[1] = point->y;
        vec[2] = point->z;
        correspondingPoint = point;
    }

    double x() const
    {
        return vec[0];
    }

    double y() const
    {
        return vec[1];
    }

    double z() const
    {
        return vec[2];
    }

    double &x()
    {
        return vec[0];
    }

    double &y()
    {
        return vec[1];
    }

    double &z()
    {
        return vec[2];
    }

    bool operator==(const TreePoint3 &p) const
    {
        return (x() == p.x()) && (y() == p.y()) && (z() == p.z());
    }

    bool  operator!=(const TreePoint3 &p) const
    {
        return !(*this == p);
    }
};
namespace CGAL
{
    template<>
    struct Kernel_traits<TreePoint3>
    {
        struct Kernel
        {
            typedef double FT;
            typedef double RT;
        };
    };
}
struct Construct_coord_iterator
{
    typedef const double *result_type;

    const double *operator()(const TreePoint3 &p) const
    {
        return static_cast<const double *>(p.vec);
    }

    const double *operator()(const TreePoint3 &p, int) const
    {
        return static_cast<const double *>(p.vec + 3);
    }
};

struct Distance
{
    typedef TreePoint3 Query_item;
    typedef double FT;
    typedef CGAL::Dimension_tag<3> D;

    double transformed_distance(const TreePoint3 &p1, const TreePoint3 &p2) const
    {
        double distx = p1.x() - p2.x();
        double disty = p1.y() - p2.y();
        double distz = p1.z() - p2.z();
        return distx * distx + disty * disty + distz * distz;
    }

    double min_distance_to_rectangle(const TreePoint3 &p,
                                     const CGAL::Kd_tree_rectangle<FT> &b) const
    {
        double distance(0.0), h = p.x();
        if (h < b.min_coord(0)) distance += (b.min_coord(0) - h) * (b.min_coord(0) - h);
        if (h > b.max_coord(0)) distance += (h - b.max_coord(0)) * (h - b.max_coord(0));
        h = p.y();
        if (h < b.min_coord(1)) distance += (b.min_coord(1) - h) * (b.min_coord(1) - h);
        if (h > b.max_coord(1)) distance += (h - b.max_coord(1)) * (h - b.min_coord(1));
        h = p.z();
        if (h < b.min_coord(2)) distance += (b.min_coord(2) - h) * (b.min_coord(2) - h);
        if (h > b.max_coord(2)) distance += (h - b.max_coord(2)) * (h - b.max_coord(2));
        return distance;
    }

    double min_distance_to_rectangle(const TreePoint3 &p,
                                     const CGAL::Kd_tree_rectangle<FT> &b, std::vector<double> &dists)
    {
        double distance(0.0), h = p.x();
        if (h < b.min_coord(0))
        {
            dists[0] = (b.min_coord(0) - h);
            distance += dists[0] * dists[0];
        }
        if (h > b.max_coord(0))
        {
            dists[0] = (h - b.max_coord(0));
            distance += dists[0] * dists[0];
        }
        h = p.y();
        if (h < b.min_coord(1))
        {
            dists[1] = (b.min_coord(1) - h);
            distance += dists[1] * dists[1];
        }
        if (h > b.max_coord(1))
        {
            dists[1] = (h - b.max_coord(1));
            distance += dists[1] * dists[1];
        }
        h = p.z();
        if (h < b.min_coord(2))
        {
            dists[2] = (b.min_coord(2) - h);
            distance += dists[2] * dists[2];
        }
        if (h > b.max_coord(2))
        {
            dists[2] = (h - b.max_coord(2));
            distance += dists[2] * dists[2];
        }
        return distance;
    }

    double max_distance_to_rectangle(const TreePoint3 &p,
                                     const CGAL::Kd_tree_rectangle<FT> &b) const
    {
        double h = p.x();
        double d0 = (h >= (b.min_coord(0) + b.max_coord(0)) / 2.0) ?
                    (h - b.min_coord(0)) * (h - b.min_coord(0)) : (b.max_coord(0) - h) * (b.max_coord(0) - h);
        h = p.y();
        double d1 = (h >= (b.min_coord(1) + b.max_coord(1)) / 2.0) ?
                    (h - b.min_coord(1)) * (h - b.min_coord(1)) : (b.max_coord(1) - h) * (b.max_coord(1) - h);
        h = p.z();
        double d2 = (h >= (b.min_coord(2) + b.max_coord(2)) / 2.0) ?
                    (h - b.min_coord(2)) * (h - b.min_coord(2)) : (b.max_coord(2) - h) * (b.max_coord(2) - h);
        return d0 + d1 + d2;
    }

    double max_distance_to_rectangle(const TreePoint3 &p,
                                     const CGAL::Kd_tree_rectangle<FT> &b, std::vector<double> &dists)
    {
        double h = p.x();
        dists[0] = (h >= (b.min_coord(0) + b.max_coord(0)) / 2.0) ?
                   (h - b.min_coord(0)) : (b.max_coord(0) - h);

        h = p.y();
        dists[1] = (h >= (b.min_coord(1) + b.max_coord(1)) / 2.0) ?
                   (h - b.min_coord(1)) : (b.max_coord(1) - h);
        h = p.z();
        dists[2] = (h >= (b.min_coord(2) + b.max_coord(2)) / 2.0) ?
                   (h - b.min_coord(2)) : (b.max_coord(2) - h);
        return dists[0] * dists[0] + dists[1] * dists[1] + dists[2] * dists[2];
    }

    double new_distance(double &dist, double old_off, double new_off,
                        int /* cutting_dimension */) const
    {
        return dist + new_off * new_off - old_off * old_off;
    }

    double transformed_distance(double d) const
    {
        return d * d;
    }

    double inverse_of_transformed_distance(double d)
    {
        return std::sqrt(d);
    }
};

typedef CGAL::Random_points_in_cube_3<TreePoint3> Random_points_iterator;
typedef CGAL::Counting_iterator<Random_points_iterator> N_Random_points_iterator;
typedef CGAL::Dimension_tag<3> D;
typedef CGAL::Search_traits<double, TreePoint3, const double *, Construct_coord_iterator> Traits;
typedef CGAL::Orthogonal_k_neighbor_search<Traits, Distance> K_neighbor_search;
typedef K_neighbor_search::Tree Tree;
typedef CGAL::Fuzzy_sphere<Traits> Fuzzy_sphere;

class Kdtree3CgalImpl
{
public:
    void insert(TreePoint3 p)
    {
        tree.insert(p);
    }

    void insert(const std::vector<TreePoint3> &points)
    {
        tree.insert(points.begin(), points.end());
    }

    TreePoint3 nearestNeighborSearch(TreePoint3 query) const
    {
        if (tree.size() == 0)
            throw std::logic_error("Nearest Neighbor Search on empty tree");

        K_neighbor_search search(tree, query);

        return search.begin()->first;
    }

    virtual double distanceToNode(TreePoint3 query) const
    {
        if (tree.size() == 0)
            return std::numeric_limits<double>::max();
        K_neighbor_search search(tree, query);

        return std::sqrt(search.begin()->second);
    }

    virtual bool hasNeighborInRange(TreePoint3 query, double range) const
    {
        Fuzzy_sphere sphere(query, range);

        std::vector<TreePoint3> foundPoints;
        tree.search(std::back_inserter(foundPoints), sphere);

        return !foundPoints.empty();
    }

private:
    Tree tree;
};

Kdtree3Cgal::Kdtree3Cgal()
{
    impl.reset(new Kdtree3CgalImpl());
}

Kdtree3Cgal::Kdtree3Cgal(const std::vector<Vector3 *> &nodes)
{
    impl.reset(new Kdtree3CgalImpl());
    insert(nodes);
}

void Kdtree3Cgal::addNode(Vector3 *node)
{
    //cachedNodes.push_back(node);
    /*

    if(cachedNodes.size() > 750)
    {
        insert(cachedNodes);
        cachedNodes.clear();
    }*/
}

void Kdtree3Cgal::insert(const std::vector<Vector3 *>& nodes)
{
    std::vector<TreePoint3> TreePoint3s;

    for (auto node : nodes)
        TreePoint3s.push_back(node);

    impl->insert(TreePoint3s);
}

void Kdtree3Cgal::insert(const std::vector<Vector3>& nodes)
{
    std::vector<TreePoint3> TreePoint3s;

    for(auto i = 0u ; i < nodes.size(); ++i) {
        TreePoint3s.push_back(TreePoint3(const_cast<Vector3*>(&nodes[i])));
    }

    impl->insert(TreePoint3s);
}


Vector3 *Kdtree3Cgal::nearestNeighborSearch(Vector3 *query) const
{
    Vector3 *foundNode = impl->nearestNeighborSearch(TreePoint3(query)).correspondingPoint;
    return foundNode;
}

double Kdtree3Cgal::distanceToClosestNeighbor(Vector3 *query) const
{
    double minDistance = impl->distanceToNode(TreePoint3(query));

    return minDistance;
}

bool Kdtree3Cgal::hasNeighborInRange(Vector3 *point, double range) const
{
    return !impl->hasNeighborInRange(point, range);
}

Kdtree3Cgal::~Kdtree3Cgal() {

}
