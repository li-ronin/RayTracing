#include "ray.h"
#include "color.h"
#include "vec3.h"

#include <iostream>

Point3 ray_color(const Ray &r)
{
    // 碰撞物体颜色
    r.hit_sphere(Point3{0.0, 0.0, -1.0}, 0.5, r); // 求出未知数t,即可求出光线r与球面的交点

    if (_t >= 0.0)
    {
        Vector Normal = unit_vector((r.A_t(_t) - Point3{0.0, 0.0, -1.0}));                  // 单位法向量[-1, 1]
        return Vector{Normal.getX() + 1.0, Normal.getY() + 1.0, Normal.getZ() + 1.0} * 0.5; // [-1, 1] --映射--> [0, 1]
    }
    // 背景颜色
    Vector unit_direction = unit_vector(r.direction());
    Color white{1.0, 1.0, 1.0};
    Color other{0.0, 0.0, 1.0};
    auto alpha = 0.5 * (unit_direction.getY() + 1.0); // alpha是两种颜色混合比例，y : [-1, 1]--映射-->[0,1]
    return white * (1.0 - alpha) + other * alpha;     // 线性插值，返回混合后的RGB颜色
}

int render()
{
    // Image
    const auto aspect_ratio = 16.0 / 9.0;
    const size_t image_width = 400;
    const size_t image_height = static_cast<int>(image_width / aspect_ratio);

    // Camera
    auto camera_height = 2.0;
    auto camera_width = 2.0 * aspect_ratio;

    Point3 origin{0.0, 0.0, 0.0};
    Point3 lower_left_corner{-camera_width / 2.0, -camera_height / 2.0, -1.0};
    Point3 horizontal{camera_width, 0.0, 0.0};
    Point3 vertical{0.0, camera_height, 0.0};

    // Render
    std::cout << "P3\n"
              << image_width << " " << image_height << std::endl;
    std::cout << "255" << std::endl;
    for (int j = image_height - 1; j >= 0; --j)
    {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i)
        {
            // 1、定义偏移量
            auto u = double(i) / image_width;
            auto v = double(j) / image_height;
            // 2、定义每条从原点到camera像素点的光线r
            Point3 pixel_center = lower_left_corner + horizontal * u + vertical * v;
            Vector ray_direction = pixel_center - origin;
            Ray r(origin, ray_direction);
            // 3、定义光线r的颜色
            Color pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
        }
    }
    std::cerr << "\n Done.\n";
    return 0;
}
