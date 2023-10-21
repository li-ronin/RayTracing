#pragma once
#include "vec3.h"

class Ray {
private:
    // 光线起始点
    Vec3 _origin;
    // 方向：单位长度的方向
    Vec3 _direction;
    // 光线长度 t 
    // 光线Ray的向量= 起始点 + 长度*方向
public:
    Ray(){}
    Ray(const Vec3& orig, const Vec3& dir)
    :_origin(orig), _direction(dir){}
    inline Vec3 origin() const {return _origin;}
    inline Vec3 direction() const {return _direction;}
    inline Vec3 A_t(double t) const{
        //_direction = _direction.unit_vector();
        return _origin + (_direction * t); 
    }
};