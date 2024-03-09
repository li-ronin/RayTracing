#include "quad.h"

Quad::Quad(const Point3 &Q, const Vector &u, const Vector &v, std::shared_ptr<Material> m)
    : _Q(Q), _u(u), _v(v), mat(m)
{
    auto n = cross(u, v);
    _normal = unit_vector(cross(u, v));
    D = dot(_normal, _Q);
    w = n / dot(n, n);
    set_bounding_box();
}

bool Quad::hit(const Ray &InRay, double ray_tmin, double ray_tmax, hit_info &rec) const
{
    // 光线没击中平面：和四边形所在的平面平行,
    auto denom = dot(_normal, InRay.direction());
    if (fabs(denom) < 1e-8)
    {
        return false;
    }
    auto step = (D - dot(_normal, InRay.origin())) / denom;
    // Return false if the hit point parameter step is outside the ray interval.
    if (step < ray_tmin || step > ray_tmax)
    {
        return false;
    }
    Point3 intersection = InRay.A_t(step);
    // 使用四边形平面内的坐标系统判断击中点intersection是否在四边形内部：QP = α.u + β.v
    Vector QP = intersection - _Q;
    auto alpha = dot(w, cross(QP, _v));
    auto beta = dot(w, cross(_u, QP));
    if (!is_interior(alpha, beta, rec))
    {
        return false;
    }
    rec.t = step;                        // 光线击中点的步长
    rec._hit_point = intersection;       // 光线击中点
    rec.mat = mat;                       // 光线击中点的材质
    rec.set_face_normal(InRay, _normal); // 光线击中点的外法线设置
    return true;
}

void Quad::set_bounding_box()
{
    bbox = AABB(_Q, _Q + _u + _v).pad();
}

AABB Quad::bounding_box() const
{
    return bbox;
}

bool Quad::is_interior(double alpha, double beta, hit_info &rec) const
{
    if ((alpha < 0) || (1 < alpha) || (beta < 0) || (1 < beta))
        return false;
    rec.u = alpha;
    rec.v = beta;
    return true;
}
