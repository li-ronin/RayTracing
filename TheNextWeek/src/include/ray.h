#pragma once
#include "vec3.h"

class Ray
{
private:
    // 光线起始点
    Point3 _origin;
    // 方向：单位长度的方向
    Vector _direction;
    // 快门 时间
    double _time;
public:
    Ray() {}
    Ray(const Point3 &orig, const Vector &dir);
    // 光线类中增加一个参数用于“运动模糊”，这个参数time在快门打开的time0时刻和关闭的时刻time1之间随机生成一条光线，然后去与运动物体求交即可
    // 这里同样需要我们封装一个运动Sphere类，它是通过定义两个圆心，在两个时间点之间进行线性插值得到某一时刻的圆心来实现，它同样继承hittable抽象类。
    Ray(const Point3 &orig, const Vector &dir, double t);
    Point3 origin() const;
    Vector direction() const;
    double time() const;
    // A_t表示光线从_origin出发，沿着_direction的方向走了步长t之后的终点
    Point3 A_t(double step) const;
};