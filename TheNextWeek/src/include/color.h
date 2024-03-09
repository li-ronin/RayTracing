#pragma once
#include "vec3.h"
#include <fstream>

using Color = Vec3;

inline void write_color(std::ofstream &file, Color pixel_color)
{
    file << static_cast<int>(255.99 * pixel_color.X()) << " "
         << static_cast<int>(255.99 * pixel_color.Y()) << " "
         << static_cast<int>(255.99 * pixel_color.Z()) << "\n";
}