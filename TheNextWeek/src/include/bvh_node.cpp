#include "bvh_node.h"


bvh_node::bvh_node(const std::vector<std::shared_ptr<hittable>> &src_objects, size_t begin, size_t end)
{   
    auto objects = src_objects;
    int axis = random_int(0, 2); // 随机选择一个轴用来划分BVH树
    auto cmp = (axis == 0) ? box_x_campare : ((axis == 1) ? box_y_campare : box_z_campare);
    size_t count = end - begin;
    if(count == 1){
        left = right = objects[begin];
    }else if(count == 2){
        if(cmp(objects[begin], objects[begin+1])){ // objects[begin].minPlane < objects[begin+1].AABB.minPlane
            left = objects[begin];
            right = objects[begin+1];
        }else{
            left = objects[begin+1];
            right = objects[begin];
        }
    }else{
        std::sort(objects.begin()+begin, objects.begin()+end, cmp);
        auto mid = begin + (end - begin)/2;
        left = std::make_shared<bvh_node>(objects, begin, mid);
        right = std::make_shared<bvh_node>(objects, mid, end);
    }
    bbox = AABB(left->bounding_box(), right->bounding_box());
}
bvh_node::bvh_node(const hittable_list &list)
    : bvh_node(list.object_list, 0, list.object_list.size()) {}
bool bvh_node::hit(const Ray &InRay, double ray_tmin, double ray_tmax, hit_info &rec) const
{
    if(!bbox.hit(InRay, ray_tmin, ray_tmax)) {
        return false;
    }
    bool hit_left = left->hit(InRay, ray_tmin, ray_tmax, rec);
    bool hit_right= right->hit(InRay, ray_tmin, hit_left ? rec.t : ray_tmax, rec);
    return hit_left || hit_right;
}
AABB bvh_node::bounding_box() const
{
    return bbox;
}