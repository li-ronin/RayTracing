
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"
//------------------
#include <iostream>


//*****************************************



int main()
{
    // World
    hittable_list world;
    world.add(std::make_shared<Sphere>(Point3{0, 0, -1}, 0.5));
    world.add(std::make_shared<Sphere>(Point3{0, -100.5, -1}, 100));
    // Camera
    Camera camera;
    camera.render(world);
    return 0;
}
