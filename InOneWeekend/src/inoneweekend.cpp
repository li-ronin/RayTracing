#include "ray.h"
#include "color.h"
#include "vec3.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"
#include <iostream>
#include <limits>

Color ray_color(const Ray &r, const hittable &world)
{
    hit_record rec;
    if (world.hit(r, 0, std::numeric_limits<double>::infinity(), rec))
    {
        return 0.5*(rec.normal + Color{1., 1., 1.}); // [-1, 1] --映射--> [0, 1]
    }
    // 背景颜色
    Vector unit_direction = unit_vector(r.direction());
    Color white{1.0, 1.0, 1.0};
    Color other{0.0, 0.0, 1.0};
    auto alpha = 0.5 * (unit_direction.getY() + 1.0); // alpha是两种颜色混合比例，y : [-1, 1]--映射-->[0,1]
    return white * (1.0 - alpha) + other * alpha;     // 线性插值，返回混合后的RGB颜色
}

void render()
{
    // Image Size
    const auto aspect_ratio = 16.0 / 9.0;
    const size_t image_width = 400;
    const size_t image_height = static_cast<int>(image_width / aspect_ratio);
    // Camera
    Camera camera;
    // World
    hittable_list world;
    world.add(std::make_shared<Sphere>(Point3{0, 0, -1}, 0.5));
    world.add(std::make_shared<Sphere>(Point3{0, -100.5, -1}, 100));
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
            Ray r = camera.get_ray(u, v);
            // 3、定义光线r的颜色
            Color pixel_color = ray_color(r, world);
            write_color(std::cout, pixel_color);
        }
    }
    std::cerr << "\n Done.\n";
}

int main()
{
    render();
    return 0;
}
