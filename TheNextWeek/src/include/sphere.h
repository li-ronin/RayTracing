//***********sphere.h**************//
#pragma once
#include "vec3.h"
#include "hittable.h"
#include <memory>

class Sphere : public hittable
{
private:
    // 球心
    Point3 _sphere_center;
    // 半径
    double _radius;
    // 材质
    std::shared_ptr<Material> _mat;
    // 包围盒，加速光线求交
    AABB bbox;
    // 运动模糊
    bool isMoving;
    // 如果是运动的物体，运动的方向
    Vector center_vec;

public:
    Sphere(Point3 center, double radius, std::shared_ptr<Material> mat);
    Sphere(Point3 center1, Point3 center2, double radius, std::shared_ptr<Material> mat);
    bool hit(const Ray &r, double ray_tmin, double ray_tmax, hit_info &rec) const override;
    AABB bounding_box() const override;
    /*
    @ get-functions
    */
    inline const double r() const { return _radius; }

    inline double &r() { return _radius; }

    inline const Point3 &center() const { return _sphere_center; }

    inline Point3 &center() { return _sphere_center; }

private:
    Point3 movedCenter(double time) const; // 在center1点沿着center_vec方向走time后的位置

    static void get_sphere_uv(const Point3 &p, double &u, double &v)
    {
        // p: a given point on the sphere of radius one, centered at the origin.
        // u: returned value [0,1] of angle around the Y axis from X=-1.
        // v: returned value [0,1] of angle from Y=-1 to Y=+1.
        //     <1 0 0> yields <0.50 0.50>       <-1  0  0> yields <0.00 0.50>
        //     <0 1 0> yields <0.50 1.00>       < 0 -1  0> yields <0.50 0.00>
        //     <0 0 1> yields <0.25 0.50>       < 0  0 -1> yields <0.75 0.50>
        const double pi = 3.1415926;
        auto theta = acos(-p.Y());
        auto phi = atan2(-p.Z(), p.X()) + pi;

        u = phi / (2 * pi);
        v = theta / pi;

        // auto phi = atan2(p.Z(), p.X());
        // auto theta = asin(p.Y());
        // u = 1 - (phi + pi) / (2 * pi);
        // v = (theta + pi / 2) / pi;
    }
};