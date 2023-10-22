//***********camera.h**************//
#pragma once
#include "ray.h"
#include "vec3.h"
class Camera {
private:
    Point3 _origin;
    Point3 _lower_left_corner;
    Point3 _horizontal;
    Point3 _vertical;
    
public:
    Camera(const Point3& O = {0., 0., 0.},
           const Point3& start = {-2., -1., -1.},
           const Point3& horizontal = {4., 0., 0.},
           const Point3& vertical = {0., 2., 0.})
           :_origin(O),
            _lower_left_corner(start),
            _horizontal(horizontal), 
            _vertical(vertical)
        {}
    inline const Ray get_ray(const double u, const double v) const
    {
        return Ray{_origin, _lower_left_corner+u*_horizontal+v*_vertical};
    }
};