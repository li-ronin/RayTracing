#pragma once
#include"utils.h"

// using Plane = Vec3; // 平行于轴的平面, 所以Plane的xyz值一定至少有两个为0

class AABB
{   
public:
    std::pair<double, double>XX;  
    std::pair<double, double>YY;  
    std::pair<double, double>ZZ;  
public:
    AABB(){}
    AABB(std::pair<double, double>_X, std::pair<double, double>_Y, std::pair<double, double>_Z);
    AABB(const Point3& a, const Point3& b);
    AABB(const AABB& box0, const AABB& box1);
    bool hit(const Ray &r, double ray_tmin, double ray_tmax) const;
    const std::pair<double, double>& Plane2(int xyz) const;
    AABB pad();
};

inline size_t size(std::pair<double, double> P)
{
    return P.second - P.first;
}

inline std::pair<double, double> expand(std::pair<double, double> P, double delta)
{
    auto padding = delta/2;
    return std::pair<double, double>{P.first - padding, P.second + padding};
}

inline AABB operator+(const AABB& box, const Vec3 &offset)
{
    std::pair<double, double> new_x = {box.XX.first + offset.X(), box.XX.second + offset.X()};
    std::pair<double, double> new_Y = {box.YY.first + offset.Y(), box.YY.second + offset.Y()};
    std::pair<double, double> new_Z = {box.ZZ.first + offset.Z(), box.ZZ.second + offset.Z()};
    return AABB(new_x, new_Y, new_Z);
}
inline AABB operator+(const Vec3 &offset, const AABB& box)
{
    return box + offset;
}