#pragma once
#include "color.h"
#include "ray.h"
#include "utils.h"
class hit_info;
class Material
{
public:
    virtual ~Material() = default;
    virtual bool scatter(const Ray &InRay, hit_info &rec, Color &attenuation, Ray &scattered) const = 0;

protected:
    /*
    @brief: find a random point in unit_sphere
    */
    const Vec3 random_unit_sphere() const
    {
        Vec3 p;
        do
        {
            p = 2.0 * Vec3(random_double(), random_double(), random_double()) - Vec3(1, 1, 1);
        } while (p.length_squared() >= 1.0);
        return p;
    }
};