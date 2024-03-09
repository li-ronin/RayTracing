#include "include/utils.h"
#include "include/camera.h"
#include "include/hittable_list.h"
#include "include/sphere.h"
#include "include/material.h"
#include "include/constant_medium.h"
#include "include/bvh_node.h"
#include "include/texture.h"
#include "include/Quad.h"
// #define STB_IMAGE_IMPLEMENTATION
// #define STB_IMAGE_STATIC
// #include "../external/stb_image.h"

//------------------
#include <iostream>

void BigScene()
{
   hittable_list world;
   auto material_ground = std::make_shared<Lambertian>(std::make_shared<Solid_Color>(Color{0.5, 0.5, 0.5}));
   world.add(std::make_shared<Sphere>(Point3(0.0, -100.5, -1.0), 100.0, material_ground));
   for (int a = -11; a < 11; a++)
   {
      for (int b = -11; b < 11; b++)
      {
         auto choose_mat = random_double();
         Point3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());
         if ((center - Point3(4, 0.2, 0)).length() > 0.9)
         {
            std::shared_ptr<Material> sphere_material;
            if (choose_mat < 0.8)
            {
               auto albedo = random_vec3() * random_vec3();
               sphere_material = std::make_shared<Lambertian>(albedo);
               world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
            }
            else if (choose_mat < 0.95)
            {
               auto albedo = random_vec3(0.5, 1);
               double fuzz = random_double(0., 0.5);
               sphere_material = std::make_shared<Metal>(albedo, fuzz);
               world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
            }
            else
            {
               sphere_material = std::make_shared<Glass>(1.5);
               world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
            }
         }
      }
   }
   auto material_center = std::make_shared<Lambertian>(std::make_shared<Solid_Color>(Color{0.5, 0.0, 0.0}));
   world.add(std::make_shared<Sphere>(Point3(-4, 1, 0), 1., material_center));

   auto material_left = std::make_shared<Glass>(1.5);
   world.add(std::make_shared<Sphere>(Point3(0, 1, 0), 1., material_left));
   // world.add(std::make_shared<Sphere>(Point3(-1.0, 0.0, -1.0), -0.45, material_left));

   auto material_right = std::make_shared<Metal>(Color(0.8, 0.6, 0.2), 0.0);
   world.add(std::make_shared<Sphere>(Point3(4.0, 1.0, 0.0), 1, material_right));
}

void Scene()
{
   hittable_list world;
   auto checker = std::make_shared<Checker_Texture>(0.8, Color(0.2, 0.3, 0.1), Color(0.9, 0.9, 0.9));
   auto material_ground = std::make_shared<Lambertian>(checker);
   world.add(std::make_shared<Sphere>(Point3(0.0, -100.5, -1.0), 100.0, material_ground));

   auto material_center = std::make_shared<Lambertian>(std::make_shared<Solid_Color>(Color{0.70, 0.80, 1.00}));
   world.add(std::make_shared<Sphere>(Point3(0, 0, -1), 0.5, material_center));

   auto material_left = std::make_shared<Glass>(1.5);
   world.add(std::make_shared<Sphere>(Point3(-1, 0, -1), 0.5, material_left));
   // world.add(std::make_shared<Sphere>(Point3(-1.0, 0.0, -1.0), -0.45, material_left));

   auto material_right = std::make_shared<Metal>(Color(0.8, 0.6, 0.2), 0.0);
   world.add(std::make_shared<Sphere>(Point3(1.0, 0, -1.0), 0.5, material_right));
}

void CheckerScene()
{
   hittable_list world;
   auto checker = std::make_shared<Checker_Texture>(0.8, Color(0.2, 0.3, 0.1), Color(0.9, 0.9, 0.9));
   world.add(std::make_shared<Sphere>(Point3(0, -10, 0), 10, std::make_shared<Lambertian>(checker)));
   world.add(std::make_shared<Sphere>(Point3(0, 10, 0), 10, std::make_shared<Lambertian>(checker)));
}

void PerlinScene()
{
   hittable_list world;
   auto pertext = std::make_shared<Noise_Texture>(4);
   world.add(std::make_shared<Sphere>(Point3(0, -1000, 0), 1000, std::make_shared<Lambertian>(pertext)));
   world.add(std::make_shared<Sphere>(Point3(0, 2, 0), 2, std::make_shared<Lambertian>(pertext)));
}

void earth()
{
   hittable_list world;
   auto earth_surface = std::make_shared<Lambertian>(std::make_shared<Image_Texture>("./src/earthmap.jpg"));
   world.add(std::make_shared<Sphere>(Point3(0, 0, 0), 2, earth_surface));
}

void Light1()
{
   hittable_list world;

   // Materials
   auto left_red = std::make_shared<Light>(Color(1.0, 0.2, 0.2));
   auto back_green = std::make_shared<Lambertian>(Color(0.2, 1.0, 0.2));
   auto right_blue = std::make_shared<Lambertian>(Color(0.2, 0.2, 1.0));
   auto upper_orange = std::make_shared<Lambertian>(Color(1.0, 0.5, 0.0));
   auto lower_teal = std::make_shared<Lambertian>(Color(0.2, 0.8, 0.8));

   // Quads
   world.add(std::make_shared<Quad>(Point3(-3, -2, 5), Vector(0, 0, -4), Vector(0, 4, 0), left_red));
   world.add(std::make_shared<Quad>(Point3(-2, -2, 0), Vector(4, 0, 0), Vector(0, 4, 0), back_green));
   world.add(std::make_shared<Quad>(Point3(3, -2, 1), Vector(0, 0, 4), Vector(0, 4, 0), right_blue));
   world.add(std::make_shared<Quad>(Point3(-2, 3, 1), Vector(4, 0, 0), Vector(0, 0, 4), upper_orange));
   world.add(std::make_shared<Quad>(Point3(-2, -3, 5), Vector(4, 0, 0), Vector(0, 0, -4), lower_teal));
}

void Light2()
{
   hittable_list world;
   auto pertext = std::make_shared<Noise_Texture>(4);
   world.add(std::make_shared<Sphere>(Point3(0, -1000, 0), 1000, std::make_shared<Lambertian>(pertext)));
   world.add(std::make_shared<Sphere>(Point3(0, 2, 0), 2, std::make_shared<Lambertian>(pertext)));

   auto difflight = std::make_shared<Light>(Color(4, 4, 4));
   world.add(std::make_shared<Quad>(Point3(3, 1, -2), Vec3(2, 0, 0), Vec3(0, 2, 0), difflight));
}

void cornell_box()
{
   hittable_list world;
   auto red = std::make_shared<Lambertian>(Color(.65, .05, .05));
   auto white = std::make_shared<Lambertian>(Color(.73, .73, .73));
   auto green = std::make_shared<Lambertian>(Color(.12, .45, .15));
   auto light = std::make_shared<Light>(Color(15, 15, 15));

   world.add(std::make_shared<Quad>(Point3(555, 0, 0), Vector(0, 555, 0), Vector(0, 0, 555), green));
   world.add(std::make_shared<Quad>(Point3(0, 0, 0), Vector(0, 555, 0), Vector(0, 0, 555), red));
   world.add(std::make_shared<Quad>(Point3(343, 554, 332), Vector(-130, 0, 0), Vector(0, 0, -105), light));
   world.add(std::make_shared<Quad>(Point3(0, 0, 0), Vector(555, 0, 0), Vector(0, 0, 555), white));
   world.add(std::make_shared<Quad>(Point3(555, 555, 555), Vector(-555, 0, 0), Vector(0, 0, -555), white));
   world.add(std::make_shared<Quad>(Point3(0, 0, 555), Vector(555, 0, 0), Vector(0, 555, 0), white));

   std::shared_ptr<hittable> box1 = box(Point3(0, 0, 0), Point3(165, 330, 165), red);
   std::shared_ptr<hittable> box2 = box(Point3(0, 0, 0), Point3(165, 165, 165), green);
   box1 = std::make_shared<Rotation_Y>(box1, 15);
   box1 = std::make_shared<Translate>(box1, Vec3(265, 0, 295));
   box2 = std::make_shared<Rotation_Y>(box2, -18);
   box2 = std::make_shared<Translate>(box2, Vec3(130, 0, 65));

   world.add(box2);
   world.add(box1);
   //
   world = hittable_list(std::make_shared<bvh_node>(world));
   // Camera
   Camera camera;
   camera.image_width = 600;       // 1200
   camera.aspect_ratio = 1;        // 16.0 / 9.0;
   camera.max_depth = 50;          // 50
   camera.samples_per_pixel = 200; // 500

   camera.vertical_fov = 40;
   camera.lookfrom = Point3(278, 278, -800); // Point3(-2, 0, -1);  3, 3, 2
   camera.lookat = Point3(278, 278, 0);      // Point3(0, 0, -1);     // 0, 0, -1
   camera.defocus_angle = 0.0;
   camera.background = Color(0, 0, 0); // 0.70, 0.80, 1.00

   camera.render(world);
}
void cornell_smoke()
{
   hittable_list world;
   auto red = std::make_shared<Lambertian>(Color(.65, .05, .05));
   auto white = std::make_shared<Lambertian>(Color(.73, .73, .73));
   auto green = std::make_shared<Lambertian>(Color(.12, .45, .15));
   auto light = std::make_shared<Light>(Color(15, 15, 15));

   world.add(std::make_shared<Quad>(Point3(555, 0, 0), Vector(0, 555, 0), Vector(0, 0, 555), green));
   world.add(std::make_shared<Quad>(Point3(0, 0, 0), Vector(0, 555, 0), Vector(0, 0, 555), red));
   world.add(std::make_shared<Quad>(Point3(343, 554, 332), Vector(-130, 0, 0), Vector(0, 0, -105), light));
   world.add(std::make_shared<Quad>(Point3(0, 0, 0), Vector(555, 0, 0), Vector(0, 0, 555), white));
   world.add(std::make_shared<Quad>(Point3(555, 555, 555), Vector(-555, 0, 0), Vector(0, 0, -555), white));
   world.add(std::make_shared<Quad>(Point3(0, 0, 555), Vector(555, 0, 0), Vector(0, 555, 0), white));

   std::shared_ptr<hittable> box1 = box(Point3(0, 0, 0), Point3(165, 330, 165), white);
   box1 = std::make_shared<Rotation_Y>(box1, 15);
   box1 = std::make_shared<Translate>(box1, Vec3(265, 0, 295));
   std::shared_ptr<hittable> box2 = box(Point3(0, 0, 0), Point3(165, 165, 165), white);
   box2 = std::make_shared<Rotation_Y>(box2, -18);
   box2 = std::make_shared<Translate>(box2, Vec3(130, 0, 65));

   world.add(std::make_shared<constant_medium>(box1, 0.01, Color(0, 0, 0)));
   world.add(std::make_shared<constant_medium>(box2, 0.01, Color(1, 1, 1)));

   //
   world = hittable_list(std::make_shared<bvh_node>(world));
   // Camera
   Camera camera;
   camera.image_width = 600;       // 1200
   camera.aspect_ratio = 1;        // 16.0 / 9.0;
   camera.max_depth = 50;          // 50
   camera.samples_per_pixel = 200; // 500

   camera.vertical_fov = 40;
   camera.lookfrom = Point3(278, 278, -800); // Point3(-2, 0, -1);  3, 3, 2
   camera.lookat = Point3(278, 278, 0);      // Point3(0, 0, -1);     // 0, 0, -1
   camera.defocus_angle = 0.0;
   camera.background = Color(0, 0, 0); // 0.70, 0.80, 1.00

   camera.render(world);
}
void test()
{
   hittable_list world;
   // auto red = std::make_shared<Metal>(Color(.65, .05, .05));
   // auto white = std::make_shared<Lambertian>(Color(.73, .73, .73));
   // auto green = std::make_shared<Metal>(Color(.12, .45, .15));

   // world.add(std::make_shared<Quad>(Point3(0, 0, 0), Vector(555, 0, 0), Vector(0, 0, 555), white));
   // world.add(std::make_shared<Sphere>(Point3(200, 80, 500), 50, green));
   // world.add(std::make_shared<Sphere>(Point3(200, 80, 150), 100, red));

   auto m1 = std::make_shared<Lambertian>(Color(0.1, 0.2, 0.5));
   auto m2 = std::make_shared<Lambertian>(Color(0.8, 0.6, 0.2));
   world.add(std::make_shared<Sphere>(Point3(0.0, 0.0, -1.0), 0.5, m1));
   world.add(std::make_shared<Sphere>(Point3(1.0, 0.0, -1.0), 0.5, m2));
}

void scene1()
{
   hittable_list world;
   hittable_list boxs;
   auto material_ground = std::make_shared<Lambertian>(Color(0.48, 0.83, 0.53));

   for (int i = 0; i < 20; i++)
   {
      for (int j = 0; j < 20; j++)
      {
         auto sideLen = 100.0;
         auto x0 = -1000.0 + i * sideLen;
         auto y0 = 0.0;
         auto z0 = -1000.0 + j * sideLen;
         auto x1 = x0 + sideLen;
         auto y1 = random_double(1, 101);
         auto z1 = z0 + sideLen;
         boxs.add(box(Point3(x0, y0, z0), Point3(x1, y1, z1), material_ground));
      }
   }

   world.add(std::make_shared<bvh_node>(boxs));
   // world = hittable_list(std::make_shared<bvh_node>(world));
   //  Camera
   Camera camera;
   camera.image_width = 600;       // 1200
   camera.aspect_ratio = 1;        // 16.0 / 9.0;
   camera.max_depth = 50;          // 50
   camera.samples_per_pixel = 200; // 500

   camera.vertical_fov = 40;
   camera.lookfrom = Point3(478, 278, -600); // Point3(-2, 0, -1);  3, 3, 2
   camera.lookat = Point3(278, 278, 0);      // Point3(0, 0, -1);     // 0, 0, -1
   camera.defocus_angle = 0.0;
   camera.background = Color(0.70, 0.80, 1.00); // 0.70, 0.80, 1.00
   camera.render(world);
}

void scene2()
{
   hittable_list world;
   auto light = std::make_shared<Light>(Color(7, 7, 7));
   world.add(std::make_shared<Quad>(Point3(123, 554, 147), Vec3(300, 0, 0), Vec3(0, 0, 265), light));
   auto center1 = Point3(400, 400, 200);
   auto center2 = center1 + Vec3(30, 0, 0);
   auto sphere_material = std::make_shared<Lambertian>(Color(0.7, 0.3, 0.1));
   world.add(std::make_shared<Sphere>(center1, center2, 50, sphere_material));
   world.add(std::make_shared<Sphere>(Point3(260, 150, 45), 50, std::make_shared<Glass>(1.5)));
   world.add(std::make_shared<Sphere>(
       Point3(0, 150, 145), 50, std::make_shared<Metal>(Color(0.8, 0.8, 0.9), 1.0)));
   world = hittable_list(std::make_shared<bvh_node>(world));
   //  Camera
   Camera camera;
   camera.image_width = 600;       // 1200
   camera.aspect_ratio = 1;        // 16.0 / 9.0;
   camera.max_depth = 50;          // 50
   camera.samples_per_pixel = 200; // 500

   camera.vertical_fov = 40;
   camera.lookfrom = Point3(478, 278, -600); // Point3(-2, 0, -1);  3, 3, 2
   camera.lookat = Point3(278, 278, 0);      // Point3(0, 0, -1);     // 0, 0, -1
   camera.defocus_angle = 0.0;
   camera.background = Color(0, 0, 0); // 0.70, 0.80, 1.00
   camera.render(world);
}

void BigScene2()
{
   hittable_list world;
   hittable_list boxs;
   auto material_ground = std::make_shared<Lambertian>(Color(0.48, 0.83, 0.53));

   for (int i = 0; i < 20; i++)
   {
      for (int j = 0; j < 20; j++)
      {
         auto sideLen = 100.0;
         auto x0 = -1000.0 + i * sideLen;
         auto y0 = 0.0;
         auto z0 = -1000.0 + j * sideLen;
         auto x1 = x0 + sideLen;
         auto y1 = random_double(1, 101);
         auto z1 = z0 + sideLen;
         boxs.add(box(Point3(x0, y0, z0), Point3(x1, y1, z1), material_ground));
      }
   }

   world.add(std::make_shared<bvh_node>(boxs));
   auto light = std::make_shared<Light>(Color(7, 7, 7));
   world.add(std::make_shared<Quad>(Point3(123, 554, 147), Vec3(300, 0, 0), Vec3(0, 0, 265), light));
   auto center1 = Point3(400, 400, 200);
   auto center2 = center1 + Vec3(30, 0, 0);
   auto sphere_material = std::make_shared<Lambertian>(Color(0.7, 0.3, 0.1));
   world.add(std::make_shared<Sphere>(center1, center2, 50, sphere_material));
   world.add(std::make_shared<Sphere>(Point3(260, 150, 45), 50, std::make_shared<Glass>(1.5)));
   world.add(std::make_shared<Sphere>(
       Point3(0, 150, 145), 50, std::make_shared<Metal>(Color(0.8, 0.8, 0.9), 1.0)));

   auto boundary = std::make_shared<Sphere>(Point3(360, 150, 145), 70, std::make_shared<Glass>(1.5));
   world.add(boundary);
   world.add(std::make_shared<constant_medium>(boundary, 0.2, Color(0.2, 0.4, 0.9)));
   boundary = std::make_shared<Sphere>(Point3(0, 0, 0), 5000, std::make_shared<Glass>(1.5));
   world.add(std::make_shared<constant_medium>(boundary, .0001, Color(1, 1, 1)));

   auto earth_surface = std::make_shared<Lambertian>(std::make_shared<Image_Texture>("./src/earthmap.jpg"));
   world.add(std::make_shared<Sphere>(Point3(400, 200, 400), 100, earth_surface));

   auto pertext_material = std::make_shared<Lambertian>(std::make_shared<Noise_Texture>(0.1));
   world.add(std::make_shared<Sphere>(Point3(220, 280, 300), 80, pertext_material));

   hittable_list boxes2;
   auto white = std::make_shared<Lambertian>(Color(.73, .73, .73));
   int ns = 1000;
   for (int j = 0; j < ns; j++)
   {
      boxes2.add(std::make_shared<Sphere>(random_vec3(0, 165), 10, white));
   }

   world.add(std::make_shared<Translate>(
       std::make_shared<Rotation_Y>(
           std::make_shared<bvh_node>(boxes2), 15),
       Vec3(-100, 270, 395)));

   world = hittable_list(std::make_shared<bvh_node>(world));
   //  Camera
   Camera camera;
   camera.image_width = 800;       // 1200
   camera.aspect_ratio = 1;        // 16.0 / 9.0;
   camera.max_depth = 40;          // 50
   camera.samples_per_pixel = 500; // 500

   camera.vertical_fov = 40;
   camera.lookfrom = Point3(478, 278, -600); // Point3(-2, 0, -1);  3, 3, 2
   camera.lookat = Point3(278, 278, 0);      // Point3(0, 0, -1);     // 0, 0, -1
   camera.defocus_angle = 0.0;
   camera.background = Color(0, 0, 0); // 0.70, 0.80, 1.00
   camera.render(world);
}
int main()
{
   // World

   // test(world);

   // 普通场景
   // Scene(world);

   // 棋盘纹理
   // CheckerScene(world);

   // 柏林噪声纹理
   // PerlinScene(world);

   // 地球图片纹理
   // earth(world);

   // 发光四边形
   // Light1(world);
   // Light2(world);

   // Cornell Box
   // cornell_box(world);
   // cornell_smoke();
   // scene2();
   BigScene2();

   // ** world_bvh中只有一个hittable，它是world合并成的bvh_node树的根节点，因为bvh_node也是hittable类型
   // ** 相当于 hittable_list world.add(hittable1, hittable2...)
   // ** bvh_node构造函数把hittable_list，也就是World，构造成一个bvh树并且返回根节点root,
   // ** 然后传进hittable_list构造函数，hittable_list构造函数仅接受shared_ptr类型，伪代码的步骤如下：
   // 1. bvh_node* root = new bvh_node(world);
   // 2. shared_ptr = make_shared<bvh_node>(root);
   // 3. hittable_list world_bvh  = hittable_list(shared_ptr);
   // 4. cam.render(world_bvh);
   // hittable_list world_bvh = hittable_list(std::make_shared<bvh_node>(world));
   // world = hittable_list(std::make_shared<bvh_node>(world));
   // // Camera

   // Camera camera;
   // camera.image_width = 600;      // 1200
   // camera.aspect_ratio = 1;   //16.0 / 9.0;
   // camera.max_depth = 50;         // 50
   // camera.samples_per_pixel = 200; // 500

   // camera.vertical_fov = 40;
   // camera.lookfrom = Point3(278, 278, -800);//Point3(-2, 0, -1);  3, 3, 2
   // camera.lookat = Point3(278, 278, 0); //Point3(0, 0, -1);     // 0, 0, -1
   // camera.defocus_angle = 0.0;
   // camera.background = Color(0, 0, 0); // 0.70, 0.80, 1.00

   // camera.render(world);
   return 0;
}
