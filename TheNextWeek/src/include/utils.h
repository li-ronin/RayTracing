#pragma once
// 工具
#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>
#include <random>
#include "ray.h"
#include "vec3.h"
// Utility Functions

//*****************************************

inline double random_double()
{
    static std::mt19937 mt;
    static std::uniform_real_distribution<double> rtrand;
    return rtrand(mt);
}
inline double random_double(double min, double max)
{
    return min + (max-min)*random_double();
}

inline int random_int(int min, int max)
{
    return static_cast<int>(random_double(min, max+1));
}

inline Vec3 random_vec3()
{
    return Vec3{random_double(), random_double(), random_double()};
}

inline Vec3 random_vec3(double min, double max)
{
    return Vec3{random_double(min, max), random_double(min, max), random_double(min, max)};
}

inline Vec3 random_unit_sphere()
{
    Vec3 p;
    do
    {
        p = 2.0 * Vec3(random_double(), random_double(), random_double()) - Vec3(1, 1, 1);
    } while (p.length_squared() >= 1.0);
    return p;
}

inline Vec3 random_unit_vector()
{
    return unit_vector(random_unit_sphere());
}

inline double degrees_to_radians(double fov) 
{
     return (fov * 3.1415926) / 180; 
}






