#pragma once
#include "vec3.h"
#include "hittable.h"

class Sphere : public hittable
{
private:
    Point3 _sphere_center;
    double _radius;

public:
    Sphere(Point3 center, double radius) : _sphere_center(center), _radius(radius) {}
    bool hit(const Ray &r, double ray_tmin, double ray_tmax, hit_record &rec) const override
    {
        // 代数求解 ax^2+bx+c = 0。其中光线r的步长t是未知数X
        Vector trace = r.origin() - _sphere_center;
        auto a = dot(r.direction(), r.direction());
        auto b = dot(r.direction(), trace) * 2;
        auto c = dot(trace, trace) - (_radius * _radius);
        auto delt = b * b - 4. * a * c;
        if (delt < 0)
            return false;
        auto t = (-b - sqrt(delt)) / (2. * a);
        if (!(ray_tmin < t && t < ray_tmax))
        {
            t = (-b + sqrt(delt)) / (2. * a);
            if (!(ray_tmin < t && t < ray_tmax))
            {
                return false;
            }
        }
        rec.t = t;
        rec.point = r.A_t(t);
        Vector outward_normal = (rec.point - _sphere_center) / _radius;
        rec.set_face_normal(r, rec.normal);
        return true;
    }
};