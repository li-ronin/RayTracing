// ---- material.h ----
#pragma once
#include "color.h"
#include "ray.h"
#include "utils.h"
#include "texture.h"

class hit_info;

class Material
{
public:
    virtual ~Material() = default;
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
    virtual bool scatter(const Ray &InRay, hit_info &rec, Color &attenuation, Ray &scattered) const = 0;
    //  发射光线的材质
    virtual Color emitted(double u, double v, const Point3 &p) const { return Color(0, 0, 0); }
};

// 漫反射材质
class Lambertian : public Material
{
private:
    std::shared_ptr<Texture> albedo;

public:
    Lambertian(const Color &c);
    Lambertian(std::shared_ptr<Texture> a);
    bool scatter(const Ray &InRay, hit_info &rec, Color &attenuation, Ray &scattered) const override;
};

// 玻璃材质
class Glass : public Material
{
private:
    double _ir;

public:
    Glass(double refraction_ratio);
    bool scatter(const Ray &InRay, hit_info &rec, Color &attenuation, Ray &scattered) const override;

private:
    // 反射
    Vector reflect(const Vector &In, const Vector &normal) const;
    // 折射
    Vector refract(const Vector &In, const Vector &Normal, double ratio, double cost) const;
    // bool refract(const Vector &In, const Vector &normal, double eta, Vector& refracted_ray) const;
    //  发生折射的概率，根据入射角和折射率得出
    double Schlick(double cosine, double ref_idx) const;
};

// 金属材质
class Metal : public Material
{
private:
    Color _albedo; // 反射之后的衰减因子
    double _fuzz;  // 模糊系数
public:
    Metal(const Color &a, const double f = 0.);
    bool scatter(const Ray &InRay, hit_info &rec, Color &attenuation, Ray &scattered) const override;

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
    Vector reflect(const Vector &InRay, const Vector &normal) const;
};

// 光源
class Light : public Material
{
private:
    std::shared_ptr<Texture> emit;

public:
    Light(const Color &c);
    Light(std::shared_ptr<Texture> e);
    bool scatter(const Ray &InRay, hit_info &rec, Color &attenuation, Ray &scattered) const override;
    Color emitted(double u, double v, const Point3 &p) const override;
};

// 各向同性类
class Isotropic : public Material
{
private:
    std::shared_ptr<Texture> albedo;
public:
    Isotropic(std::shared_ptr<Texture> a);
    Isotropic(Color c);
    bool scatter(const Ray &InRay, hit_info &rec, Color &attenuation, Ray &scattered) const override;
};