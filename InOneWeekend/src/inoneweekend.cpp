#include <iostream>
#include "ray.h"

double sphere_normal(const Vec3& center, double radius, const Ray &r) {
    Vec3 trace = r.origin()-center;
    auto a = r.direction().dot(r.direction());
    auto b = r.direction().dot(trace) *2;
    auto c = trace.dot(trace)- (radius*radius);
    auto delt = b*b - 4.*a*c;
    return delt<0 ? -1 : ((-b-sqrt(delt))/(2.*a));
}

Vec3 ray_color(const Ray &r) {
    double _t = sphere_normal(Vec3{0.0, 0.0, -1.0}, 0.5, r);        // 求出未知数t,即可求出光线r与球面的交点
    if(_t >= 0.0)
    {
        Vec3 Normal = (r.A_t(_t) - Vec3{0.0, 0.0, -1.0}).unit_vector();                 // 单位法向量[-1, 1]
        return Vec3{Normal.getX() + 1.0, Normal.getY() + 1.0, Normal.getZ() + 1.0}*0.5; // [-1, 1] --映射--> [0, 1]
    }
    Vec3 unit_direction = r.direction().unit_vector();
    Vec3 color_white{1.0, 1.0, 1.0};
    Vec3 color_other{0.0, 0.0, 1.0};
    auto alpha = 0.5*(unit_direction.getY() + 1.0);     // alpha是两种颜色混合比例，y : [-1, 1]--映射-->[0,1]
    return color_white*(1.0-alpha) + color_other*alpha; // 线性插值，返回混合后的RGB颜色
}

int render() {
    // Image
    const auto aspect_ratio = 16.0 / 9.0;
    const size_t image_width  = 400;
    const size_t image_height = static_cast<int>(image_width / aspect_ratio);
    
    // Camera
    auto camera_height = 2.0;
    auto camera_width  = 2.0 * aspect_ratio;

    Vec3 origin(0.0, 0.0, 0.0);
    Vec3 lower_left_corner(-camera_width/2.0, -camera_height/2.0, -1.0);
    Vec3 horizontal(camera_width, 0.0, 0.0);
    Vec3 vertical(0.0, camera_height, 0.0);

    std::cout<<"P3\n"<<image_width<<" "<<image_height<<std::endl;
    std::cout<<"255"<<std::endl;
    for (int j = image_height-1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            // 1、定义偏移量
            auto u = double(i) / image_width;
            auto v = double(j) / image_height;
            // 2、定义每条从原点到camera像素点的光线r
            Ray r(origin, lower_left_corner + horizontal*u + vertical*v);
            // 3、定义光线r的颜色
            Vec3 color_r = ray_color(r);     
            color_r.write_color(std::cout);
        }
    }
    std::cerr<<"\n Done.\n";
    return 0;
}
