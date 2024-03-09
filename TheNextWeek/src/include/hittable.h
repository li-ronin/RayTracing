//***********hittable.h**********//
#pragma once
#include "aabb.h"
#include "ray.h"
#include <memory>

class Material;

/**
 * @brief 光线与物体的碰撞信息
 */
class hit_info
{
public:
  Point3 _hit_point; // 碰撞点point
  Vector normal;     // 碰撞点处法线
  double t;          // 光线长度t
  double u, v;       // 击中点的uv信息
  bool ray_is_outward;
  std::shared_ptr<Material> mat;

  /**
   * 设置碰撞点信息，包括碰撞点处法线向量、法线朝向
   */
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
    // 单位法向量，没有位置信息
    normal = ray_is_outward ? outward_normal : -outward_normal;
  }
};

// 抽象类:检测光线与物体是否有碰撞
class hittable
{
public:
  virtual ~hittable() = default;
  virtual bool hit(const Ray &r, double ray_tmin, double ray_tmax, hit_info &rec) const = 0;
  virtual AABB bounding_box() const = 0;
};