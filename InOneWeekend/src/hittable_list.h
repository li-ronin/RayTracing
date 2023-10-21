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
    hittable_list(std::shared_ptr<hittable> object) { add(object); }
    void clear() { object_list.clear(); }
    void add(std::shared_ptr<hittable> object)
    {
        object_list.push_back(object);
    }
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
                closest_so_far = temp_rec.t;
                rec = temp_rec;
            }
        }
        return hit_anything;
    }
};