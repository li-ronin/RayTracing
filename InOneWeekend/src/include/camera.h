//***********camera.h**************//
#pragma once
#include "ray.h"
#include "vec3.h"
#include "color.h"
#include "utils.h"
#include "hittable_list.h"
#include <limits>

class Camera
{

private:
    Point3 _origin;
    size_t image_height;
    Vector vector_u, vector_v, vector_w;   // 相机倾斜角度
    double defocus_radius;       // 虚焦半径
public:
    Point3 _lower_left_corner;
    Point3 _horizontal;
    Point3 _vertical;
    double aspect_ratio = 16.0 / 9.0;
    size_t image_width = 800;
    size_t samples_per_pixel = 100;
    size_t max_depth = 10;
    double vertical_fov = 90;
    Point3 lookfrom{-2, 2, 1};
    Point3 lookat{0, 0, -1};
    Vector camera_up{0., 1.0, 0.};
    double defocus_angle;
    double focus_dist = 3.4;

    void render(const hittable &world);

private:
    void initialize();
    Color ray_color(const Ray &InRay, int depth, const hittable &world);
    inline const Ray get_ray(const double basis_u, const double basis_v) const
    {
        Point3 unit_offset = defocus_radius * random_unit_disk();
        Point3 offset = vector_u*unit_offset[0] + vector_v*unit_offset[1]; 
        return Ray{_origin+offset, _lower_left_corner + basis_u * _horizontal + basis_v * _vertical - (_origin+offset)};
    }
    inline double degrees_to_radians(double fov) { return (fov * 3.1415926) / 180; }
    Point3 random_unit_disk() const
    {
        while(true)
        {
            auto p = Point3{random_double(), random_double(), 0};
            if(p.length_squared()<=1)return p;
        }
    }
};


// 实现

void Camera::render(const hittable &world)
{
    initialize();
    std::string fileName;
    std::cout << "请输入文件名称: ";
    std::cin >> fileName;
    std::ofstream file("./images/"+ fileName +".ppm");
    if (file.is_open())
    {
        file << "P3\n" << image_width << " " << image_height << "\n255\n";
        for (int j = image_height - 1; j >= 0; --j)
        {
            std::cout << "\rScanlines remaining: " << j << ' ' << std::endl;
            for (int i = 0; i < image_width; ++i)
            {
                Color pixel_color;
                // 抗锯齿
                for (int cnt = 0; cnt < samples_per_pixel; cnt++)
                {
                    double u = double(i + random_double()) / image_width;
                    double v = double(j + random_double()) / image_height;
                    Ray r = get_ray(u, v);
                    pixel_color += ray_color(r, max_depth, world);
                }
                pixel_color /= samples_per_pixel;
                // 颜色 伽马校正（颜色浅一点）
                pixel_color = Color{ sqrt(pixel_color.X()), sqrt(pixel_color.Y()), sqrt(pixel_color.Z()) };
                write_color(file, pixel_color);
            }
        }
        file.close();
        std::cout << "\n Finished!!!.\n";
    }
    else
    {
        std::cerr << "load file failed!" << std::endl;
    }
}
void Camera::initialize()
{
    // 最终生成图像的高度
    image_height = static_cast<int>(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;
    // 相机的位置
    _origin = lookfrom;
    // 相机视线夹角参数
    double theta = degrees_to_radians(vertical_fov);
    double height_ratio = tan(theta / 2);
    double width_ratio = aspect_ratio * height_ratio;
    focus_dist = (lookat-lookfrom).length();
    defocus_radius = tan(degrees_to_radians(defocus_angle / 2)) * focus_dist;
    vector_w = unit_vector(lookfrom - lookat);
    vector_u = unit_vector(cross(vector_w, camera_up));
    vector_v = cross(vector_u, vector_w);
    
    // 屏幕的左下角坐标
    _lower_left_corner = _origin - ((height_ratio * vector_v) + (width_ratio * vector_u) + vector_w) * focus_dist;
    // 屏幕的高度和宽度的大小值，后续加在左下角坐标上作为偏移量
    _vertical = 2 * height_ratio * focus_dist * vector_v;
    _horizontal = 2 * width_ratio * focus_dist * vector_u;
}
Color Camera::ray_color(const Ray &InRay, int depth, const hittable &world)
{
    if (depth <= 0)
        return Color{0., 0., 0.};
    hit_info rec;
    if (world.hit(InRay, 0.001, std::numeric_limits<double>::infinity(), rec))
    {
        Ray scattered;     // 反射光线
        Color attenuation; // 颜色衰减系数
        // 根据碰撞体的材质设置其反射光线和反射光线的衰减系数
        if (rec.mat->scatter(InRay, rec, attenuation, scattered))
        {
            return attenuation * ray_color(scattered, depth - 1, world);
        }
        return Color{0., 0., 0.};
    }
    // 背景颜色
    Vector unit_direction = unit_vector(InRay.direction());
    Color white{1.0, 1.0, 1.0};
    Color other{0.5, 0.7, 1.0};
    auto alpha = 0.5 * (unit_direction.Y() + 1.0); // alpha是两种颜色混合比例，y : [-1, 1]--映射-->[0,1]
    return white * (1.0 - alpha) + other * alpha;  // 线性插值，返回混合后的RGB颜色
}