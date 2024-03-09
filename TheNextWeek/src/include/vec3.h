#pragma once
#include <iostream>
#include <cmath>

class Vec3
{
private:
    // 0.0-1.0之间的三个数字
    double e[3];

public:
    Vec3();
    Vec3(double d);
    Vec3(double e0, double e1, double e2);

public:
    double X() const;
    double Y() const;
    double Z() const;
    // 操作符重载
    Vec3 operator-() const;
    double operator[](size_t i) const;
    double &operator[](size_t i);

    Vec3 &operator+=(const Vec3 &v);
    Vec3 &operator-=(const Vec3 &v);
    Vec3 &operator*=(double d);
    Vec3 &operator/=(double d);

    double length() const;
    double length_squared() const;

    bool near_zero() const;
};

// Vector Utility Functions
inline std::ostream &operator<<(std::ostream &out, const Vec3 &v)
{
    return out << v.X() << ' ' << v.Y() << ' ' << v.Z();
}
inline Vec3 operator+(const Vec3 &u, const Vec3 &v)
{
    return Vec3{u.X() + v.X(), u.Y() + v.Y(), u.Z() + v.Z()};
}
inline Vec3 operator-(const Vec3 &u, const Vec3 &v)
{
    return Vec3{u.X() - v.X(), u.Y() - v.Y(), u.Z() - v.Z()};
}
inline Vec3 operator*(const Vec3 &v, double d)
{
    return Vec3{d * v.X(), d * v.Y(), d * v.Z()};
}
inline Vec3 operator*(double d, const Vec3 &v)
{
    return v * d;
}
inline Vec3 operator*(const Vec3 &u, const Vec3 &v)
{
    return Vec3{u.X() * v.X(), u.Y() * v.Y(), u.Z() * v.Z()};
}
inline Vec3 operator/(const Vec3 &v, double d)
{
    return v * (1 / d);
}

// 向量点乘
inline double dot(const Vec3 &u, const Vec3 &v)
{
    return u.X() * v.X() + u.Y() * v.Y() + u.Z() * v.Z();
}

// 向量叉乘
/**
 * | a1 a2 a3|
 * | b1 b2 b3|  =
 * | i  j  k |
 */
inline Vec3 cross(const Vec3 &u, const Vec3 &v)
{
    return Vec3{u.Y() * v.Z() - u.Z() * v.Y(),
                u.Z() * v.X() - u.X() * v.Z(),
                u.X() * v.Y() - u.Y() * v.X()};
}
// 单位化向量
inline Vec3 unit_vector(Vec3 v)
{
    return v / v.length();
}

// Vec3类可以用来表示颜色、位置、向量的三维
using Point3 = Vec3;
using Vector = Vec3;