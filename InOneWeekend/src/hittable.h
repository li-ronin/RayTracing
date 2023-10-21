//***********hittable.h**********//
#pragma once
#include "ray.h"

class hit_record
{
public:
  Point3 point;  // 碰撞点point
  Vector normal; // 碰撞点处法线
  double t;      // 光线长度t
  bool ray_is_outward;

  void set_face_normal(const Ray &r, const Vector &outward_normal)
  {
    if (dot(r.direction(), outward_normal) < 0) // 光线方向和曲面外法线的方向相反的话说明光朝着曲面内部射 --->(
    {
      ray_is_outward = true; //  --->(
    }
    else
    {
      ray_is_outward = false; //  --->)
    }
    normal = ray_is_outward ? outward_normal : -outward_normal;
  }
};

// 抽象类:检测光线与物体是否有碰撞
class hittable
{
public:
  virtual ~hittable() = default;
  virtual bool hit(const Ray &r, double ray_tmin, double ray_tmax, hit_record &rec) const = 0;
};