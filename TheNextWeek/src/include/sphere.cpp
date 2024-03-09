#include "sphere.h"

Sphere::Sphere(Point3 center, double radius, std::shared_ptr<Material> mat)
    : _sphere_center(center), _radius(radius), _mat(mat), isMoving(false)
{   
    if(radius>0){
        auto r_vec = Vec3{radius, radius, radius};
        bbox = AABB(center - r_vec, center + r_vec);
    }else{
        auto r_vec = Vec3{-radius, -radius, -radius};
        bbox = AABB(center - r_vec, center + r_vec);
    }
    
}
Sphere::Sphere(Point3 center1, Point3 center2, double radius, std::shared_ptr<Material> mat)
    : _sphere_center(center1), _radius(radius), _mat(mat), isMoving(true)
{
    auto r_vec = Vec3{radius, radius, radius};
    AABB box1{center1 - r_vec, center1 + r_vec};
    AABB box2{center2 - r_vec, center2 + r_vec};
    bbox = AABB(box1, box2);
    center_vec = center2 - center1;
}

AABB Sphere::bounding_box() const { return bbox; }

Point3 Sphere::movedCenter(double time) const
{
    return _sphere_center + (center_vec * time);
}

bool Sphere::hit(const Ray &r, double ray_tmin, double ray_tmax, hit_info &rec) const
{
    // 此球心是center1向center2方向随机移动一段距离的球心，移动的距离与Ray的time有关
    Point3 center = isMoving ? movedCenter(r.time()) : _sphere_center; // r.time()为[0, 1]的随机数
    // 代数求解 ax^2+bx+c = 0。其中光线r的步长t是未知数X
    Vector trace = r.origin() - center;
    auto a = dot(r.direction(), r.direction());
    auto b = dot(r.direction(), trace) * 2;
    auto c = dot(trace, trace) - (_radius * _radius);
    auto delt = b * b - 4. * a * c;
    if (delt < 0)
        return false;
    auto t = (-b - sqrt(delt)) / (2. * a);
    if (!(ray_tmin < t && t < ray_tmax))
    {
        
        t = (-b + sqrt(delt)) / (2. * a);
        if (!(ray_tmin < t && t < ray_tmax))
        {
            return false;
        }
    }
    rec.t = t;
    rec._hit_point = r.A_t(t);
    rec.mat = _mat;
    Vector outward_normal = unit_vector(rec._hit_point - _sphere_center);
    rec.set_face_normal(r, outward_normal);
    get_sphere_uv(outward_normal, rec.u, rec.v);
    return true;
}