#pragma once
#include "vec3.h"

using Color = Vec3;

void write_color(std::ostream &out, Color pixel_color)
{
    out << static_cast<int>(255.99 * pixel_color.X()) << " "
        << static_cast<int>(255.99 * pixel_color.Y()) << " "
        << static_cast<int>(255.99 * pixel_color.Z()) << "\n";
}