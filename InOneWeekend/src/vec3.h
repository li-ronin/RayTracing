#pragma once
#include <iostream>
#include <cmath>
// 用来表示颜色、位置的三维向量
class Vec3 {
private:
    // 0.0-1.0之间的三个数字
    double e[3];
public:
    Vec3() : e{0, 0, 0}{}
    Vec3(double d):e{d, d, d}{}
    Vec3(double e0, double e1, double e2):e{e0, e1, e2}{}
public:
    double getX() const;
    double getY() const;
    double getZ() const;
    // 操作符重载
    double operator[](size_t i) const;
    double& operator[](size_t i);
    Vec3& Add(const Vec3& v);
    Vec3& Sub(const Vec3& v);
    Vec3& Multiply(double d);
    Vec3& Divide(double d);

    Vec3& operator+=(const Vec3 &v);
    Vec3& operator-=(const Vec3 &v);
    Vec3& operator*=(double d);
    Vec3& operator/=(double d);

    Vec3 operator+(const Vec3 &v)const;
    Vec3 operator-(const Vec3 &v)const;
    Vec3 operator*(double d)const;
    Vec3 operator/(double d)const;
    friend std::ostream& operator<<(std::ostream& os, const Vec3& vec);
    // 向量点乘
    double dot(const Vec3 &v);
    
    // 单位化向量
    inline Vec3 unit_vector() {
        Vec3 res = *this;
        return  res / res.length();
    }

    // 求向量大小
    double length() const {
        return sqrt(length_squared());
    }
    double length_squared() const {
        return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
    }
    void write_color(std::ostream &out);
};