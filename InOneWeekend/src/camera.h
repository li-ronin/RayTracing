//***********camera.h**************//
#pragma once
#include "ray.h"
#include "vec3.h"
#include "color.h"
#include <random>
#include <limits>
#include <format>
std::mt19937 seed;
std::uniform_real_distribution<double> randDouble;

class Camera
{
private:
    Point3 _origin;
    Point3 _lower_left_corner;
    Point3 _horizontal;
    Point3 _vertical;
    double aspect_ratio = 16.0/9.0;
    size_t image_width = 400;
    size_t image_height;

public:
    Camera(const Point3 &O = {0., 0., 0.},
           const Point3 &start = {-2., -1., -1.},
           const Point3 &horizontal = {4., 0., 0.},
           const Point3 &vertical = {0., 2., 0.})
        : _origin(O),
          _lower_left_corner(start),
          _horizontal(horizontal),
          _vertical(vertical)
    {}

    inline const Ray get_ray(const double u, const double v) const
    {
        return Ray{_origin, _lower_left_corner + u * _horizontal + v * _vertical};
    }

    void render(const hittable &world)
    {
        initialize();
        std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";
        for (int j = image_height - 1; j >= 0; --j)
        {
            std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
            for (int i = 0; i < image_width; ++i)
            {
                Color pixel_color;
                // 抗锯齿：取中心点周围50个像素点的颜色的均值
                for (int cnt = 0; cnt < 50; cnt++)
                {
                    double u = double(i + randDouble(seed)) / image_width;
                    double v = double(j + randDouble(seed)) / image_height;
                    Ray r = get_ray(u, v);
                    pixel_color += ray_color(r, world);
                }
                pixel_color /= 50;
                write_color(std::cout, pixel_color);
            }
        }
        std::cerr << "\n Done.\n";
    }

private:
    void initialize()
    { 
        image_height =  static_cast<int>(image_width / aspect_ratio);
        image_height = (image_height < 1) ? 1 : image_height;
    }
    Color ray_color(const Ray &r, const hittable &world)
    {
        hit_record rec;
        if (world.hit(r, 0, std::numeric_limits<double>::infinity(), rec))
        {
            return 0.5 * (rec.normal + Color{1., 1., 1.}); // [-1, 1] --映射--> [0, 1]
        }
        // 背景颜色
        Vector unit_direction = unit_vector(r.direction());
        Color white{1.0, 1.0, 1.0};
        Color other{0.0, 0.0, 1.0};
        auto alpha = 0.5 * (unit_direction.getY() + 1.0); // alpha是两种颜色混合比例，y : [-1, 1]--映射-->[0,1]
        return white * (1.0 - alpha) + other * alpha;     // 线性插值，返回混合后的RGB颜色
    }
};