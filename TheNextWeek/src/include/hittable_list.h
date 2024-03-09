//***********hittable_list.h**************//
#pragma once
#include "aabb.h"
#include "hittable.h"
#include <vector>
#include <memory>

class hittable_list : public hittable
{
public:
    std::vector<std::shared_ptr<hittable>> object_list;
    AABB bbox;

public:
    hittable_list() {}
    hittable_list(std::shared_ptr<hittable> object);
    void clear();
    void add(std::shared_ptr<hittable> object);
    // 对于一条光线r，它的路径上可能存在多个物体，我们取离原点最近的碰撞点信息rec存下来
    bool hit(const Ray &r, double ray_tmin, double ray_tmax, hit_info &rec) const override;
    AABB bounding_box() const override;
};




class Translate : public hittable
{
private:
    std::shared_ptr<hittable> object;
    Vec3 offset;
    AABB bbox;

public:
    Translate(std::shared_ptr<hittable> obj, const Vec3& off);
    bool hit(const Ray &r, double ray_tmin, double ray_tmax, hit_info &rec) const override;
    AABB bounding_box() const override;
};




class Rotation_Y : public hittable
{
private:
    std::shared_ptr<hittable> object;
    double sin_theta;
    double cos_theta;
    AABB bbox;

public:
    Rotation_Y(std::shared_ptr<hittable> obj, double angle);
    bool hit(const Ray &r, double ray_tmin, double ray_tmax, hit_info &rec) const override;
    AABB bounding_box() const override;
};