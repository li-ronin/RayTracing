#include "constant_medium.h"

constant_medium::constant_medium(std::shared_ptr<hittable> b, double d, std::shared_ptr<Texture> a)
    : boundary(b), neg_inv_density(-1 / d), phase_function(std::make_shared<Isotropic>(a)) {}

constant_medium::constant_medium(std::shared_ptr<hittable> b, double d, Color c)
    : boundary(b), neg_inv_density(-1 / d), phase_function(std::make_shared<Isotropic>(c)) {}

bool constant_medium::hit(const Ray &InRay, double ray_tmin, double ray_tmax, hit_info &rec) const
{
    // debugging的时候把enableDebug设置为true
    const bool enableDebug = false;
    const bool debugging = enableDebug && random_double() < 0.00001;
    const double infinity = std::numeric_limits<double>::infinity();
    hit_info rec1;
    hit_info rec2;
    if (!boundary->hit(InRay, -infinity, infinity, rec1))
    {
        return false;
    }
    if (!boundary->hit(InRay, rec1.t + 0.0001, infinity, rec2))
    {
        return false;
    }
    if (debugging)
    {
        std::clog << "\nray_tmin=" << rec1.t << ", ray_tmax=" << rec2.t << '\n';
    }
    if (rec1.t < ray_tmin)
        rec1.t = ray_tmin;
    if (rec2.t > ray_tmax)
        rec2.t = ray_tmax;
    if (rec1.t >= rec2.t)
        return false;
    if (rec1.t < 0)
        rec1.t = 0;
    auto ray_length = InRay.direction().length();
    auto distance_inside_boundary = (rec2.t - rec1.t) * ray_length;
    auto hit_distance = neg_inv_density * log(random_double());
    if (hit_distance > distance_inside_boundary)
        return false;
    rec.t = rec1.t + hit_distance / ray_length;
    rec._hit_point = InRay.A_t(rec.t);
    if (debugging)
    {
        std::clog << "hit_distance = " << hit_distance << '\n'
                  << "rec.t = " << rec.t << '\n'
                  << "rec.p = " << rec._hit_point << '\n';
    }
    rec.normal = Vec3(1, 0, 0);
    rec.ray_is_outward = true;
    rec.mat = phase_function;
    return true;
}
AABB constant_medium::bounding_box() const
{
    return boundary->bounding_box();
}