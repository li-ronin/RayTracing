#include "ray.h"

Ray::Ray(const Point3 &orig, const Vector &dir): _origin(orig), _direction(dir), _time(0) {}

Ray::Ray(const Point3 &orig, const Vector &dir, double t = 0.0): _origin(orig), _direction(dir), _time(t) {}

Point3 Ray::origin() const { return _origin; }

Vector Ray::direction() const { return _direction; }
double Ray::time() const {return _time;}
// A_t表示光线从_origin出发，沿着_direction的方向走了步长t之后的终点
Point3 Ray::A_t(double step) const
{
    return _origin + (_direction * step);
}