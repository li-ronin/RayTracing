#include "camera.h"
#include <cstring>

void Camera::initialize()
{
    // 最终生成图像的高度
    image_height = static_cast<int>(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;
    // 相机的位置
    _camera_origin = lookfrom;
    // 相机视线夹角参数
    double theta = degrees_to_radians(vertical_fov);
    double height_ratio = tan(theta / 2);
    double width_ratio = aspect_ratio * height_ratio;
    focus_dist = (lookat - lookfrom).length();
    defocus_radius = tan(degrees_to_radians(defocus_angle / 2)) * focus_dist;
    vector_w = unit_vector(lookfrom - lookat);
    vector_u = unit_vector(cross(camera_up, vector_w));
    vector_v = cross(vector_w, vector_u);

    // 屏幕的左下角坐标
    _lower_left_corner = _camera_origin - ((height_ratio * vector_v) + (width_ratio * vector_u) + vector_w) * focus_dist;
    // 屏幕的高度和宽度的大小值，后续加在左下角坐标上作为偏移量
    _vertical = 2 * height_ratio * focus_dist * vector_v;
    _horizontal = 2 * width_ratio * focus_dist * vector_u;
}

void Camera::render(const hittable_list &world)
{
    initialize();
    std::string fileName;
    std::cout << "Input the image filename: ";
    std::cin >> fileName;
    std::ofstream file("./images/" + fileName + ".ppm");
    if (file.is_open())
    {
        file << "P3\n"
             << image_width << " " << image_height << "\n255\n";
        for (int j = image_height - 1; j >= 0; --j)
        {
            std::cout << "\rScanlines remaining: " << j << ' ' << std::flush;
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
                pixel_color = Color{sqrt(pixel_color.X()), sqrt(pixel_color.Y()), sqrt(pixel_color.Z())};
                write_color(file, pixel_color);
            }
        }
        file.close();
        std::cout << "\n Finished!!!.\n";
    }
    else
    {
        std::cerr << "Error opening file '"
                  << "./images/" << fileName << ".ppm': " << std::strerror(errno) << std::endl;
    }
}

const Ray Camera::get_ray(const double basis_u, const double basis_v) const
{
    // defocus_radius是透镜的半径，单位圆(半径为1的圆)内生成随机一点 × 透镜的半径 = 在透镜内生成一个随机点
    Point3 unit_offset = defocus_radius * random_unit_disk();
    // 将透镜随机点的倾斜角度转到和相机相同
    Point3 offset = vector_u * unit_offset[0] + vector_v * unit_offset[1];
    // 将透镜随机点的位置移动到相机中心
    Point3 ray_origin = _camera_origin + offset;
    Vector ray_direction = _lower_left_corner + (basis_u * _horizontal) + (basis_v * _vertical) - ray_origin;
    double ray_time = random_double();  // [0, 1]的随机数
    return Ray{ray_origin, ray_direction, ray_time};
}

// 返回光线的颜色
Color Camera::ray_color(const Ray &InRay, int depth, const hittable_list &world)
{
    if (depth <= 0)
        return Color{0., 0., 0.};
    hit_info rec;
    if (world.hit(InRay, 0.001, std::numeric_limits<double>::infinity(), rec))
    {
        Ray scattered;     // 反射光线
        Color attenuation; // 颜色衰减系数
        Color color_emission = rec.mat->emitted(rec.u, rec.v, rec._hit_point);
        // 根据碰撞体的材质设置其反射光线和反射光线的衰减系数
        if (rec.mat->scatter(InRay, rec, attenuation, scattered))
        {
            return color_emission + attenuation * ray_color(scattered, depth - 1, world);
        }
        return color_emission;
    }
    return background;  
}

