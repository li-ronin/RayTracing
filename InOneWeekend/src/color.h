#pragma once
#include "vec3.h"

using Color = Vec3;

void write_color(std::ostream &out, Color pixel_color)
{
    out << static_cast<int>(255.99 * pixel_color.getX()) << " "
        << static_cast<int>(255.99 * pixel_color.getY()) << " "
        << static_cast<int>(255.99 * pixel_color.getZ()) << "\n";
}