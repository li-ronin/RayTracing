#pragma once
// 工具
#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>
#include <random>

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


inline Vec3 random_vec3()
{
    return Vec3{random_double(), random_double(), random_double()};
}
inline Vec3 random_vec3(double min, double max)
{
    return Vec3{random_double(min, max), random_double(min, max), random_double(min, max)};
}