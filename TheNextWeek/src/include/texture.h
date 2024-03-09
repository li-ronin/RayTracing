#pragma once
#include "utils.h"
#include "color.h"
#include "perlin.h"
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_STATIC
#include "../external/stb_image.h"

class Texture
{
public:
    virtual ~Texture() = default;
    virtual Color value(double u, double v, const Point3 &p) const = 0;
};

// 纯色的纹理
class Solid_Color : public Texture
{
private:
    Color color_value;

public:
    Solid_Color(Color c);
    Solid_Color(double r, double g, double b);
    Color value(double u, double v, const Point3 &p) const override;
};

// 棋盘纹理
class Checker_Texture : public Texture
{
private:
    double checker_scale;
    std::shared_ptr<Texture> even;
    std::shared_ptr<Texture> odd;

public:
    Checker_Texture(double _scale, Color c1, Color c2);
    Checker_Texture(double _scale, std::shared_ptr<Texture> t0, std::shared_ptr<Texture> t1);
    Color value(double u, double v, const Point3 &p) const override;
};

// 柏林噪声纹理
class Noise_Texture : public Texture
{
private:
    Perlin noise;
    double scale;

public:
    Noise_Texture() {}
    Noise_Texture(double sc);
    Color value(double u, double v, const Point3 &p) const override;
};

// 图片纹理
class Image_Texture : public Texture
{
private:
    unsigned char *data;
    int width, height;
    const int bytes_per_pixel = 3;
    int bytes_per_scanline;
public:
    Image_Texture() : data(nullptr), width(0), height(0) {}
    Image_Texture(unsigned char *pixels, int A, int B);
    Image_Texture(const char *filename);
    ~Image_Texture();
    Color value(double u, double v, const Point3 &p) const override;

private:
    static int clamp(int x, int low, int high)
    {
        // Return the value clamped to the range [low, high).
        if (x < low)
            return low;
        if (x < high)
            return x;
        return high - 1;
    }
};
