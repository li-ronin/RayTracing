//***********camera.h**************//
#pragma once
#include "ray.h"
#include "vec3.h"
#include "color.h"
#include "utils.h"
#include "hittable_list.h"
#include"material.h"
#include <limits>

class Camera
{

private:
    Point3 _camera_origin;      // 相机位置
    size_t image_height;
    Vector vector_u, vector_v, vector_w;    
    double defocus_radius;       // 虚焦半径
public:
    Point3 _lower_left_corner;
    Point3 _horizontal; 
    Point3 _vertical;
    double aspect_ratio = 16.0 / 9.0;
    size_t image_width = 800;
    size_t samples_per_pixel = 100; // 像素点抗锯齿采样次数
    size_t max_depth = 10;          // 光线的反射的最大次数
    Color  background;              // 背景颜色
    double vertical_fov = 90;   
    Point3 lookfrom{-2, 2, 1};
    Point3 lookat{0, 0, -1};
    Vector camera_up{0., 1.0, 0.};
    double defocus_angle;
    double focus_dist;    // 焦距 = (lookat-lookfrom).length();
    void render(const hittable_list &world);

private:
    void initialize();
    Color ray_color(const Ray &InRay, int depth, const hittable_list &world);
    const Ray get_ray(const double basis_u, const double basis_v) const;
};



inline Point3 random_unit_disk()
{
    while(true)
    {
        auto p = Point3{random_double(), random_double(), 0};
        if(p.length_squared()<=1)return p;
    }
}