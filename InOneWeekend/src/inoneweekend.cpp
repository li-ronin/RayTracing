#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"
#include "metal.h"
#include "lambertian.h"
#include "glass.h"
//------------------
#include <iostream>

int main()
{
   // World
   hittable_list world;
   auto material_ground = std::make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
   world.add(std::make_shared<Sphere>(Point3{0, -1000, 0}, 1000, material_ground));
   for (int a = -11; a <= 11; a++)
   {
      for (int b = -11; b <= 11; b++)
      {
          double choose_meterial = random_double();
          Point3 center = Point3{a + 0.9*random_double(), 0.2, b + 0.9*random_double()};
          if((center-Point3{4,0.2,0}).length()>0.9)
          {
              std::shared_ptr<Material> sphere_material;
              if(choose_meterial<=0.3)
              {
                  Color albedo = random_vec3() * random_vec3();
                  sphere_material = std::make_shared<Lambertian>(albedo);  
              }else if(choose_meterial<=0.6)
              {
                  Color  albedo = random_vec3(0.5, 1);
                  double fuzz = random_double(0, 0.5);  
                  sphere_material = std::make_shared<Metal>(albedo, fuzz); 
              }else
              {
                  sphere_material = std::make_shared<Glass>(1.5); 
              }
              world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
          }
      }
   }

   auto material1 = std::make_shared<Glass>(1.5);
   world.add(std::make_shared<Sphere>(Point3(0, 1, 0), 1.0, material1));

   auto material2 = std::make_shared<Lambertian>(Color(0.4, 0.2, 0.1));
   world.add(std::make_shared<Sphere>(Point3(-4, 1, 0), 1.0, material2));

   auto material3 = std::make_shared<Metal>(Color(0.7, 0.6, 0.5), 0.0);
   world.add(std::make_shared<Sphere>(Point3(4, 1, 0), 1.0, material3));
   // Camera
   Camera camera;
   camera.image_width = 200;   // 1200
   camera.aspect_ratio = 16.0 / 9.0;
   camera.max_depth = 50;
   camera.samples_per_pixel = 50; //500
   camera.vertical_fov = 20;
   camera.lookfrom = Point3(13, 2, 3);
   camera.lookat = Point3(0, 0, 0);
   camera.defocus_angle = 0.6;
   camera.render(world);
   return 0;
}



