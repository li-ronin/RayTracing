#include "vec3.h"

Vec3::Vec3() : e{0., 0., 0.} {}
Vec3::Vec3(double d) : e{d, d, d} {}
Vec3::Vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

double Vec3::X() const { return e[0]; }
double Vec3::Y() const { return e[1]; }
double Vec3::Z() const { return e[2]; }
// 操作符重载
Vec3 Vec3::operator-() const { return Vec3(-e[0], -e[1], -e[2]); }
double Vec3::operator[](size_t i) const { return e[i]; }
double &Vec3::operator[](size_t i) { return e[i]; }

Vec3 &Vec3::operator+=(const Vec3 &v)
{
    e[0] += v.e[0];
    e[1] += v.e[1];
    e[2] += v.e[2];
    return *this;
}
Vec3 &Vec3::operator-=(const Vec3 &v)
{
    e[0] -= v.e[0];
    e[1] -= v.e[1];
    e[2] -= v.e[2];
    return *this;
}
Vec3 &Vec3::operator*=(double d)
{
    e[0] *= d;
    e[1] *= d;
    e[2] *= d;
    return *this;
}
Vec3 &Vec3::operator/=(double d)
{
    return *this *= 1 / d;
}
double Vec3::length() const
{
    return sqrt(length_squared());
}
double Vec3::length_squared() const
{
    return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
}
bool Vec3::near_zero() const
{
    auto s = 1e-8;
    return (fabs(e[0]) <= s) && (fabs(e[1]) <= s) && (fabs(e[2]) <= s);
}