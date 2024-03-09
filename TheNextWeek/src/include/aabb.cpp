#include "aabb.h"

// AABB::AABB()
// {
//     XX = std::pair<double, double>{INT_MAX, INT_MIN};
//     YY = std::pair<double, double>{INT_MAX, INT_MIN};
//     ZZ = std::pair<double, double>{INT_MAX, INT_MIN};
// }
AABB::AABB(std::pair<double, double> _X, std::pair<double, double> _Y, std::pair<double, double> _Z)
    : XX(_X), YY(_Y), ZZ(_Z) {}
AABB::AABB(const Point3 &a, const Point3 &b)
{
    /**
     *      ________
     *     /       /|
     *    a_______/ |
     *    |       | |
     *    |       | b
     *    |_______|/
     */
    XX = std::pair<double, double>{fmin(a[0], b[0]), fmax(a[0], b[0])};
    YY = std::pair<double, double>{fmin(a[1], b[1]), fmax(a[1], b[1])};
    ZZ = std::pair<double, double>{fmin(a[2], b[2]), fmax(a[2], b[2])};
}

AABB::AABB(const AABB &box0, const AABB &box1)
{
    XX = std::pair<double, double>{fmin(box0.XX.first, box1.XX.first), fmax(box0.XX.second, box1.XX.second)};
    YY = std::pair<double, double>{fmin(box0.YY.first, box1.YY.first), fmax(box0.YY.second, box1.YY.second)};
    ZZ = std::pair<double, double>{fmin(box0.ZZ.first, box1.ZZ.first), fmax(box0.ZZ.second, box1.ZZ.second)};
}

const std::pair<double, double> &AABB::Plane2(int xyz) const
{
    if (xyz == 0)
        return XX;
    else if (xyz == 1)
        return YY;
    return ZZ;
}
bool AABB::hit(const Ray &InRay, double ray_tmin, double ray_tmax) const
{
    // AABB 里面暂时不更新碰撞点信息rec的内容
    for (int a = 0; a < 3; a++)
    {
        /**
         *  X(step) = Origin + step*Direction;
         *  step = (X-Origin)/Direction;
         */
        auto inv_dir = 1 / InRay.direction()[a];
        auto orig = InRay.origin()[a];
        auto step0 = (Plane2(a).first - orig) * inv_dir;
        auto step1 = (Plane2(a).second - orig) * inv_dir;
        if (inv_dir < 0)
        {
            std::swap(step0, step1);
        }
        if (ray_tmin < step0)
            ray_tmin = step0;
        if (ray_tmax > step1)
            ray_tmax = step1;
        if (ray_tmin >= ray_tmax)
            return false;
    }
    return true;
}

AABB AABB::pad()
{
    // Return an AABB that has no side narrower than some delta, padding if necessary.
    double delta = 0.0001;
    std::pair<double, double> new_x = (size(XX) >= delta) ? XX : expand(XX, delta);
    std::pair<double, double> new_y = (size(YY) >= delta) ? YY : expand(YY, delta);
    std::pair<double, double> new_z = (size(ZZ) >= delta) ? ZZ : expand(ZZ, delta);
    return AABB(new_x, new_y, new_z);
}


