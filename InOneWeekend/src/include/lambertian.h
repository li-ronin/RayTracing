#pragma once
#include "material.h"

// 漫反射材质
class Lambertian : public Material
{
private:
    Color _albedo; // 漫反射系数
public:
    Lambertian(const Color &a) : _albedo(a) {}

    /**
     * @brief: 根据材质来设置反射光线 和 衰减系数
     *
     * @param InRay:   入射光线
     * @param rec: 碰撞信息
     * @param attenuation: 颜色的衰减
     * @param scattered 散射光线
     *
     * @return: 是否存在合法撞击点
     */
    bool scatter(const Ray &InRay, hit_info &rec, Color &attenuation, Ray &scattered) const override
    {
        Point3 scatter_direction =  random_unit_sphere() + rec.normal;
        if (scatter_direction.near_zero())scatter_direction = rec.normal;
        scattered = Ray{rec._hit_point, scatter_direction};
        attenuation = _albedo;

        return true;
    }
};