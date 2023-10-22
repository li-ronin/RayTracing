//***********hittable_list.h**************//
#pragma once
#include "hittable.h"
#include <vector>
#include <memory>

class hittable_list : public hittable
{
private:
    std::vector<std::shared_ptr<hittable>> object_list;

public:
    hittable_list(){}
    hittable_list(std::shared_ptr<hittable> object) { add(object); }
    void clear() { object_list.clear(); }
    void add(std::shared_ptr<hittable> object)
    {
        object_list.push_back(object);
    }
    // 对于一条光线r，它的路径上可能存在多个物体，我们取离原点最近的碰撞点信息rec存下来
    bool hit(const Ray &r, double ray_tmin, double ray_tmax, hit_record &rec) const override
    {
        hit_record temp_rec;
        bool hit_anything = false;
        auto closest_so_far = ray_tmax;
        for(const auto& obj : object_list)
        {
            if(obj->hit(r, ray_tmin, closest_so_far, temp_rec))
            {
                hit_anything = true;
                closest_so_far = temp_rec.t; // 把t的最远距离更新为上一次碰撞点的距离
                rec = temp_rec;
            }
        }
        return hit_anything;
    }
};