// constant_medium.h
#pragma once
#include "vec3.h"
#include "hittable.h"
#include "material.h"
//-------------------------
#include <memory>

class constant_medium : public hittable
{
private:
    std::shared_ptr<hittable> boundary;
    std::shared_ptr<Material> phase_function;
    double neg_inv_density;

public:
    constant_medium(std::shared_ptr<hittable> b, double d, std::shared_ptr<Texture> a);
    constant_medium(std::shared_ptr<hittable> b, double d, Color c);
    bool hit(const Ray &r, double ray_tmin, double ray_tmax, hit_info &rec) const;
    AABB bounding_box() const;
};