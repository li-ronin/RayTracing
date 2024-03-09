//***********bvh_node.h**************//
#pragma once
#include "utils.h"
#include "hittable.h"
#include "hittable_list.h"
#include <algorithm>

/**
 *  BVH树，节点的包括：值是AABB包围盒、左、右孩子节点
 *
 */
class bvh_node : public hittable
{
private:
    AABB bbox;
    std::shared_ptr<hittable> left;     // hittable是一个泛型   我们让left指向一个Sphere类 left->bounding_box()即可获得该Sphere的包围盒
    std::shared_ptr<hittable> right;
public:
    bvh_node(const std::vector<std::shared_ptr<hittable>> &objects, size_t begin, size_t end);
    bvh_node(const hittable_list &list);
    bool hit(const Ray &r, double ray_tmin, double ray_tmax, hit_info &rec) const override;
    AABB bounding_box() const override;

private:
    static bool box_campare(const std::shared_ptr<hittable> a, const std::shared_ptr<hittable> b, int xyz)
    {
        return a->bounding_box().Plane2(xyz).first < b->bounding_box().Plane2(xyz).first;
    }
    static bool box_x_campare(const std::shared_ptr<hittable> a, const std::shared_ptr<hittable> b)
    {
        return box_campare(a, b, 0);
    }
    static bool box_y_campare(const std::shared_ptr<hittable> a, const std::shared_ptr<hittable> b)
    {
        return box_campare(a, b, 1);
    }
    static bool box_z_campare(const std::shared_ptr<hittable> a, const std::shared_ptr<hittable> b)
    {
        return box_campare(a, b, 2);
    }
};