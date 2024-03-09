#include "material.h"
#include "hittable.h"
/**
 * 漫反射材质类
 */
Lambertian::Lambertian(const Color &c) : albedo(std::make_shared<Solid_Color>(c)) {}
Lambertian::Lambertian(std::shared_ptr<Texture> a) : albedo(a) {}

bool Lambertian::scatter(const Ray &InRay, hit_info &rec, Color &attenuation, Ray &scattered) const
{
    Point3 scatter_direction = random_unit_sphere() + rec.normal;
    if (scatter_direction.near_zero())
        scatter_direction = rec.normal;
    scattered = Ray{rec._hit_point, scatter_direction, InRay.time()};
    attenuation = albedo->value(rec.u, rec.v, rec._hit_point);
    return true;
}

/**
 * 玻璃材质类
 */
Glass::Glass(double refraction_ratio) : _ir(refraction_ratio) {}

bool Glass::scatter(const Ray &InRay, hit_info &rec, Color &attenuation, Ray &scattered) const
{
    attenuation = Color{1., 1., 1.};
    double refraction_ratio = rec.ray_is_outward ? (1 / _ir) : _ir;
    Vector unit_direction = unit_vector(InRay.direction());
    double cos_t = fmin(dot(-unit_direction, rec.normal), 1);
    double sin_t = sqrt(1 - cos_t * cos_t);
    Vector refract_vector;
    if (refraction_ratio * sin_t > 1 || Schlick(cos_t, refraction_ratio) > random_double())
    {
        // 全反射（没有折射）
        refract_vector = reflect(unit_direction, rec.normal);
    }
    else
    {
        // 折射（只有折射）
        refract_vector = refract(unit_direction, rec.normal, refraction_ratio, cos_t);
    }
    scattered = Ray{rec._hit_point, refract_vector, InRay.time()};
    return true;
}
// 反射
Vector Glass::reflect(const Vector &In, const Vector &normal) const
{
    return In - 2 * dot(In, normal) * normal;
}
// 折射
Vector Glass::refract(const Vector &In, const Vector &normal, double ratio, double cost) const
{
    Vector R1 = ratio * (In + cost * normal);
    Vector R2 = -sqrt(fabs(1 - R1.length_squared())) * normal;
    return R1 + R2;
}

// 发生折射的概率，根据入射角和折射率得出
double Glass::Schlick(double cosine, double ref_idx) const
{
    auto r0 = (1 - ref_idx) / (1 + ref_idx);
    r0 = r0 * r0;
    return r0 + (1 - r0) * pow((1 - cosine), 5);
}

/**
 * 金属材质类
 */
Metal::Metal(const Color &a, const double f) : _albedo(a)
{
    _fuzz = (f < 1) ? f : 1.0;
}

bool Metal::scatter(const Ray &InRay, hit_info &rec, Color &attenuation, Ray &scattered) const
{
    Vector reflect_direction = reflect(unit_vector(InRay.direction()), rec.normal);
    scattered = Ray{rec._hit_point, reflect_direction + _fuzz * random_unit_sphere(), InRay.time()};
    attenuation = _albedo;
    return dot(reflect_direction, rec.normal) > 0;
}

Vector Metal::reflect(const Vector &In, const Vector &normal) const
{
    return In - 2 * dot(In, normal) * normal;
}

// 光源/发光材质
Light::Light(const Color &c) : emit(std::make_shared<Solid_Color>(c)) {}
Light::Light(std::shared_ptr<Texture> e) : emit(e) {}
bool Light::scatter(const Ray &InRay, hit_info &rec, Color &attenuation, Ray &scattered) const
{
    return false;
}
Color Light::emitted(double u, double v, const Point3 &p) const
{
    return emit->value(u, v, p);
}

// 各向同性类
Isotropic::Isotropic(std::shared_ptr<Texture> a)
    : albedo(a) {}

Isotropic::Isotropic(Color c)
    : albedo(std::make_shared<Solid_Color>(c)) {}

bool Isotropic::scatter(const Ray &InRay, hit_info &rec, Color &attenuation, Ray &scattered) const
{
    scattered = Ray(rec._hit_point, random_unit_vector(), InRay.time());
    attenuation = albedo->value(rec.u, rec.v, rec._hit_point);
    return true;
}