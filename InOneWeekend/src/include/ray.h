#pragma once
#include "vec3.h"

class Ray
{
private:
    // 光线起始点
    Point3 _origin;
    // 方向：单位长度的方向
    Vector _direction;

public:
    Ray() {}
    Ray(const Point3 &orig, const Vector &dir)
        : _origin(orig), _direction(dir) {}
    inline Point3 origin() const { return _origin; }
    inline Vector direction() const { return _direction; }
    // A_t表示光线从_origin出发，沿着_direction的方向走了步长t之后的终点
    inline Point3 A_t(double t) const
    {
        return _origin + (_direction * t);
    }
};