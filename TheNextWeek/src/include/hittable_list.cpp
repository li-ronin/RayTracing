#include "hittable_list.h"

// class hittable_list
hittable_list::hittable_list(std::shared_ptr<hittable> object)
{
    add(object);
}

void hittable_list::clear()
{
    object_list.clear();
}

void hittable_list::add(std::shared_ptr<hittable> object)
{
    object_list.push_back(object);
    bbox = AABB(bbox, object->bounding_box());
}

// 对于一条光线r，它的路径上可能存在多个物体，我们取离原点最近的碰撞点信息rec存下来
bool hittable_list::hit(const Ray &r, double ray_tmin, double ray_tmax, hit_info &rec) const
{
    hit_info temp_rec;
    bool hit_anything = false;
    auto closest_so_far = ray_tmax;
    for (const auto &obj : object_list)
    {
        if (obj->hit(r, ray_tmin, closest_so_far, temp_rec))
        {
            hit_anything = true;
            closest_so_far = temp_rec.t; // 把t的最远距离更新为上一次碰撞点的距离
            rec = temp_rec;
        }
    }
    return hit_anything;
}

AABB hittable_list::bounding_box() const { return bbox; }



// Translate

Translate::Translate(std::shared_ptr<hittable> obj, const Vec3 &off)
    : object(obj), offset(off)
{
    bbox = object->bounding_box() + offset;
}

bool Translate::hit(const Ray &InRay, double ray_tmin, double ray_tmax, hit_info &rec) const
{
    Ray offset_R(InRay.origin() - offset, InRay.direction(), InRay.time());
    if (!object->hit(offset_R, ray_tmin, ray_tmax, rec))
    {
        return false;
    }
    rec._hit_point += offset;
    rec.set_face_normal(offset_R, rec.normal);
    return true;
}


AABB Translate::bounding_box() const
{
    return bbox;
}



// Roattion_Y
Rotation_Y::Rotation_Y(std::shared_ptr<hittable> obj, double angle)
    : object(obj)
{
    auto radians = degrees_to_radians(angle);
    sin_theta = sin(radians);
    cos_theta = cos(radians);
    bbox = object->bounding_box();
    const double infinity = std::numeric_limits<double>::infinity();
    Point3 min(infinity, infinity, infinity);
    Point3 max(-infinity, -infinity, -infinity);

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            for (int k = 0; k < 2; k++)
            {
                auto x = i * bbox.XX.second + (1 - i) * bbox.XX.first;
                auto y = j * bbox.YY.second + (1 - j) * bbox.YY.first;
                auto z = k * bbox.ZZ.second + (1 - k) * bbox.ZZ.first;

                auto newx = cos_theta * x + sin_theta * z;
                auto newz = -sin_theta * x + cos_theta * z;

                Vec3 tester(newx, y, newz);

                for (int c = 0; c < 3; c++)
                {
                    min[c] = fmin(min[c], tester[c]);
                    max[c] = fmax(max[c], tester[c]);
                }
            }
        }
    }
    bbox = AABB(min, max);
}
bool Rotation_Y::hit(const Ray &InRay, double ray_tmin, double ray_tmax, hit_info &rec) const
{
    Point3 origin = InRay.origin();
    Vector direction = InRay.direction();
    origin[0] = cos_theta * InRay.origin()[0] - sin_theta * InRay.origin()[2];
    origin[2] = cos_theta * InRay.origin()[2] + sin_theta * InRay.origin()[0];
    direction[0] = cos_theta * InRay.direction()[0] - sin_theta * InRay.direction()[2];
    direction[2] = sin_theta * InRay.direction()[0] + cos_theta * InRay.direction()[2];
    Ray Rotate_R(origin, direction, InRay.time());
    if (!object->hit(Rotate_R, ray_tmin, ray_tmax, rec))
    {
        return false;
    }
    Point3 p = rec._hit_point;
    Vector n = rec.normal;
    p[0] = cos_theta * rec._hit_point[0] + sin_theta * rec._hit_point[2];
    p[2] = cos_theta * rec._hit_point[2] - sin_theta * rec._hit_point[0];
    n[0] = cos_theta * rec.normal[0] + sin_theta * rec.normal[2];
    n[2] = cos_theta * rec.normal[2] - sin_theta * rec.normal[0];
    rec._hit_point = p;
    rec.normal = n;
    return true;
}
AABB Rotation_Y::bounding_box() const
{
    return bbox;
}