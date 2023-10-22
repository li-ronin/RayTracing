#pragma once
#include <iostream>
#include <cmath>

class Vec3
{
private:
    // 0.0-1.0之间的三个数字
    double e[3];

public:
    Vec3() : e{0., 0., 0.} {}
    Vec3(double d) : e{d, d, d} {}
    Vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

public:
    double getX() const { return e[0]; }
    double getY() const { return e[1]; }
    double getZ() const { return e[2]; }
    // 操作符重载
    Vec3 operator-() const { return Vec3(-e[0], -e[1], -e[2]); }
    double operator[](size_t i) const { return e[i]; }
    double &operator[](size_t i) { return e[i]; }

    Vec3 &operator+=(const Vec3 &v)
    {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }
    Vec3 &operator-=(const Vec3 &v)
    {
        e[0] -= v.e[0];
        e[1] -= v.e[1];
        e[2] -= v.e[2];
        return *this;
    }
    Vec3 &operator*=(double d)
    {
        e[0] *= d;
        e[1] *= d;
        e[2] *= d;
        return *this;
    }
    Vec3 &operator/=(double d)
    {
        return *this *= 1 / d;
    }

    double length() const
    {
        return sqrt(length_squared());
    }
    double length_squared() const
    {
        return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
    }
};

// Vector Utility Functions
inline std::ostream &operator<<(std::ostream &out, const Vec3 &v)
{
    return out << v.getX() << ' ' << v.getY() << ' ' << v.getZ();
}
inline Vec3 operator+(const Vec3 &u, const Vec3 &v)
{
    return Vec3{u.getX() + v.getX(), u.getY() + v.getY(), u.getZ() + v.getZ()};
}
inline Vec3 operator-(const Vec3 &u, const Vec3 &v)
{
    return Vec3{u.getX() - v.getX(), u.getY() - v.getY(), u.getZ() - v.getZ()};
}
inline Vec3 operator*(const Vec3 &v, double d)
{
    return Vec3{d * v.getX(), d * v.getY(), d * v.getZ()};
}
inline Vec3 operator*(double d, const Vec3 &v)
{
    return v * d;
}
inline Vec3 operator/(const Vec3 &v,  double d)
{
    return v * (1 / d);
}


// 向量点乘
double dot(const Vec3 &u, const Vec3 &v)
{
    return u.getX() * v.getX() + u.getY() * v.getY() + u.getZ() * v.getZ();
}

// 单位化向量
inline Vec3 unit_vector(Vec3 v)
{
    return v / v.length();
}

// Vec3类可以用来表示颜色、位置、向量的三维
using Point3 = Vec3;
using Vector = Vec3;