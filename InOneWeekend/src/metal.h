#pragma once
#include "material.h"

// 金属材质
class Metal : public Material
{
private:
    Color  _albedo;   // 反射之后的衰减因子
    double _fuzz;     // 模糊系数
public:
    Metal(const Color &a, const double f=0.) : _albedo(a) 
    {
        _fuzz = (0<=f && f<1)?f:1.0;
    }

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
        Vector reflect_direction = reflect(unit_vector(InRay.direction()), rec.normal);
        scattered = Ray{rec._hit_point, reflect_direction + _fuzz*random_unit_sphere()};
        attenuation = _albedo;
        return dot(reflect_direction, rec.normal) != 0;
    }

protected:
    /*
    反射定律：
    假设入射光线为R，反射光线为B，如何光线的反向光线A = -R。
    A + B = 2倍的 A在法向量N上的投影（也是个向量）
    A在法向量N上的投影的长度=（A·N）= |A||N|cosθ   因为|N|==1,所以是A在N上的投影的长度
    A在法向量N上的投影的 =（A·N）× N
    于是A+B = 2（A·N）× N
    我们要求的就是反射光线 B = -A +2（A·N）× N = R - 2 (R·N）× N
    */
    Vector reflect(const Vector &InRay, const Vector &normal) const
    {
        return InRay - 2 * dot(InRay, normal) * normal;
    }
};