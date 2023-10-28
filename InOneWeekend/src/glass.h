#pragma once
#include "material.h"
#include "hittable.h"

class Glass : public Material
{
private:
    double _ir;

public:
    Glass(double refraction_ratio):_ir(refraction_ratio) {}

    bool scatter(const Ray &InRay, hit_info &rec, Color &attenuation, Ray &scattered) const override
    {
        attenuation = Color{1.,1.,1.};
        double refraction_ratio = rec.ray_is_outward ? (1/_ir) : _ir;
        Vector unit_direction = unit_vector(InRay.direction());
        double cos_t = fmin(dot(-unit_direction, rec.normal), 1);
        double sint = sqrt(1-cos_t*cos_t);
        Vector refract_vector;
        if(refraction_ratio * sint > 1 || Schlick(cos_t, refraction_ratio) > random_double()){
            // 全反射（没有折射）
            refract_vector = reflect(unit_direction, rec.normal);
        }else{
            // 折射（只有折射）
            refract_vector = refract(unit_direction, rec.normal, refraction_ratio, cos_t);
        }
        scattered = Ray(rec._hit_point, refract_vector);
        return true;
    }

private:
    // 反射
    Vector reflect(const Vector &In, const Vector &normal) const
    {
        return In - 2 * dot(In, normal) * normal;
    }
    // 折射
    Vector refract(const Vector &In, const Vector &Normal, double ratio, double cost) const
    {
        Vector R1 = ratio * (In + cost*Normal);
        Vector R2 = - sqrt(fabs(1-R1.length_squared())) * Normal;
        return R1+R2;
    }
    // 发生折射的概率，根据入射角和折射率得出
    double Schlick(double cosine, double ref_idx) const
    {
        auto r0 = (1-ref_idx) / (1+ref_idx);
        r0 = r0*r0;
        return r0 + (1-r0)*pow((1 - cosine),5);
    }
};