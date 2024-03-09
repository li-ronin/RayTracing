#pragma once
#include "vec3.h"
#include "hittable.h"
#include "hittable_list.h"
//-------------------------
#include <memory>
#include <cmath>

/**
 *  Ax + By + Cz = D
 * 我们使用3个概念来定义出四边形
 *  左下角 Q
 *  方向向量 u 和 v
 *      /u
 *     /
 *    Q —— ——>v
 */
class Quad : public hittable
{
private:
    Point3 _Q;
    Vector _u, _v; // uv的大小即为四边形的是边长大小
    std::shared_ptr<Material> mat;
    AABB bbox;
    Vector _normal; // (A, B, C)
    double D;       //  D = Ax + By + Cz = _normal · X  X为平面上任意一点
    Vector w;       // 一个判断光线的击中点是否在四边形内部的量，w = n / n·(u × v) = n / n·n

public:
    Quad(const Point3 &Q, const Vector &u, const Vector &v, std::shared_ptr<Material> m);
    bool hit(const Ray &r, double ray_tmin, double ray_tmax, hit_info &rec) const override;
    AABB bounding_box() const override;
    virtual void set_bounding_box();
    virtual bool is_interior(double alpha, double beta, hit_info &rec) const;
};

// 6个四边形的面围成一个立方体，a,b为两个对角点
inline std::shared_ptr<hittable_list> box(const Point3 &a, const Point3 &b, std::shared_ptr<Material> mat)
{
    // Returns the 3D box (six sides) that contains the two opposite vertices a & b.

    auto sides = std::make_shared<hittable_list>();

    // Construct the two opposite vertices with the minimum and maximum coordinates.
    auto min = Point3(fmin(a.X(), b.X()), fmin(a.Y(), b.Y()), fmin(a.Z(), b.Z()));
    auto max = Point3(fmax(a.X(), b.X()), fmax(a.Y(), b.Y()), fmax(a.Z(), b.Z()));

    auto dx = Vec3(max.X() - min.X(), 0, 0);
    auto dy = Vec3(0, max.Y() - min.Y(), 0);
    auto dz = Vec3(0, 0, max.Z() - min.Z());

    sides->add(std::make_shared<Quad>(Point3(min.X(), min.Y(), max.Z()), dx, dy, mat));  // front
    sides->add(std::make_shared<Quad>(Point3(max.X(), min.Y(), max.Z()), -dz, dy, mat)); // right
    sides->add(std::make_shared<Quad>(Point3(max.X(), min.Y(), min.Z()), -dx, dy, mat)); // back
    sides->add(std::make_shared<Quad>(Point3(min.X(), min.Y(), min.Z()), dz, dy, mat));  // left
    sides->add(std::make_shared<Quad>(Point3(min.X(), max.Y(), max.Z()), dx, -dz, mat)); // top
    sides->add(std::make_shared<Quad>(Point3(min.X(), min.Y(), min.Z()), dx, dz, mat));  // bottom

    return sides;
}

class Cube : public hittable
{
public:
    Cube() {}
    Cube(const Point3 &p0, const Point3 &p1, std::shared_ptr<Material> M);

    bool hit(const Ray &r, double t0, double t1, hit_info &rec) const override;

    AABB bounding_box() const override;

public:
    Point3 box_min;
    Point3 box_max;
    hittable_list sides;
};