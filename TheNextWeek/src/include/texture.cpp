#include "texture.h"

// Solid_Color类
Solid_Color::Solid_Color(Color c)
    : color_value(c) {}
Solid_Color::Solid_Color(double r, double g, double b)
    : color_value(Color{r, g, b}) {}
Color Solid_Color::value(double u, double v, const Point3 &p) const
{
    return color_value;
}

// Checker_Texture类
Checker_Texture::Checker_Texture(double _scale, Color c1, Color c2)
    : checker_scale(1/_scale),
      even(std::make_shared<Solid_Color>(c1)),
      odd(std::make_shared<Solid_Color>(c2))
{
}
Checker_Texture::Checker_Texture(double _scale, std::shared_ptr<Texture> t0, std::shared_ptr<Texture> t1)
    : checker_scale(1/_scale), even(t0), odd(t1) {}
Color Checker_Texture::value(double u, double v, const Point3 &p) const
{
    int xPos = static_cast<int>(std::floor(checker_scale * p.X()));
    int yPos = static_cast<int>(std::floor(checker_scale * p.Y()));
    int zPos = static_cast<int>(std::floor(checker_scale * p.Z()));
    bool isEven = (xPos + yPos + zPos) % 2 == 0;
    return isEven ? even->value(u, v, p) : odd->value(u, v, p);
}

// Noise_Texture类
Noise_Texture::Noise_Texture(double sc) : scale(sc) {}
Color Noise_Texture::value(double u, double v, const Point3 &p) const
{
    auto s = scale * p;
    return Color{1, 1, 1} * 0.5 * (1 + sin(s.Z() + 10 * noise.turb(s)));
}

// Image_Texture类

Image_Texture::Image_Texture(unsigned char *_d, int w, int h)
    : data(_d), width(w), height(h) {}

Image_Texture::Image_Texture(const char *filename)
{
    auto n = bytes_per_pixel; // Dummy out parameter: original components per pixel
    data = stbi_load(filename, &width, &height, &n, bytes_per_pixel); // 0
    bytes_per_scanline = width * bytes_per_pixel;
}
Image_Texture::~Image_Texture()
{
    delete data;
}

Color Image_Texture::value(double u, double v, const Vec3 &p) const
{
    // If we have no texture data, then always emit cyan (as a debugging aid).
    if (data == nullptr || height <= 0)
        return Color(0, 1, 1);
    //u = clamp(u, 0.0, 1.0);
    //v = 1.0 - clamp(v, 0.0, 1.0); // Flip V to image coordinates

    auto i = static_cast<int>(u * width);
    auto j = static_cast<int>((1-v) * height - 0.001);
    if (i < 0)
        i = 0;
    if (j < 0)
        j = 0;
    if (i >= width)
        i = width - 1;
    if (j >= height)
        j = height - 1;

    auto r = static_cast<int>(data[3 * i + 3 * width * j + 0]) / 255.0;
    auto g = static_cast<int>(data[3 * i + 3 * width * j + 1]) / 255.0;
    auto b = static_cast<int>(data[3 * i + 3 * width * j + 2]) / 255.0;

    return Color{r, g, b};
}