#pragma once
#include "utils.h"

class Perlin
{
public:
    Perlin()
    {
        ranvec = new Vec3[point_count];
        for (int i = 0; i < point_count; ++i)
        {
            ranvec[i] = random_vec3(-1, 1);
        }
        perm_x = perlin_generate_perm();
        perm_y = perlin_generate_perm();
        perm_z = perlin_generate_perm();
    }

    ~Perlin()
    {
        delete[] ranvec;
        delete[] perm_x;
        delete[] perm_y;
        delete[] perm_z;
    }

    double noise(const Point3 &p) const
    {
        auto u = p.X() - floor(p.X());
        auto v = p.Y() - floor(p.Y());
        auto w = p.Z() - floor(p.Z());
        u = u * u * (3 - 2 * u);
        v = v * v * (3 - 2 * v);
        w = w * w * (3 - 2 * w);
        auto i = static_cast<int>(floor(p.X()));
        auto j = static_cast<int>(floor(p.Y()));
        auto k = static_cast<int>(floor(p.Z()));
        Vec3 c[2][2][2];

        for (int di = 0; di < 2; di++)
            for (int dj = 0; dj < 2; dj++)
                for (int dk = 0; dk < 2; dk++)
                    c[di][dj][dk] = ranvec[perm_x[(i + di) & 255] ^
                                           perm_y[(j + dj) & 255] ^
                                           perm_z[(k + dk) & 255]];

        return perlin_interp(c, u, v, w);
    }
    // 湍流
    double turb(const Point3& p, int depth=7) const {
        auto accum = 0.0;
        auto temp_p = p;
        auto weight = 1.0;

        for (int i = 0; i < depth; i++) {
            accum += weight*noise(temp_p);
            weight *= 0.5;
            temp_p *= 2;
        }

        return fabs(accum);
    }
private:
    static const int point_count = 256;
    // double *ranfloat;
    Vec3 *ranvec;
    int *perm_x;
    int *perm_y;
    int *perm_z;
    static double perlin_interp(Vec3 c[2][2][2], double u, double v, double w)
    {
        auto uu = u * u * (3 - 2 * u);
        auto vv = v * v * (3 - 2 * v);
        auto ww = w * w * (3 - 2 * w);
        auto accum = 0.0;

        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 2; j++)
                for (int k = 0; k < 2; k++)
                {
                    Vec3 weight_v(u - i, v - j, w - k);
                    accum += (i * uu + (1 - i) * (1 - uu)) 
                            * (j * vv + (1 - j) * (1 - vv)) 
                            * (k * ww + (1 - k) * (1 - ww)) 
                            * dot(c[i][j][k], weight_v);
                }

        return accum;
    }
    static int *perlin_generate_perm()
    {
        auto p = new int[point_count];

        for (int i = 0; i < Perlin::point_count; i++)
            p[i] = i;

        permute(p, point_count);

        return p;
    }

    static void permute(int *p, int n)
    {
        for (int i = n - 1; i > 0; i--)
        {
            int target = random_int(0, i);
            int tmp = p[i];
            p[i] = p[target];
            p[target] = tmp;
        }
    }
};