#include"include/color.h"

#include "include/hittable_list.h"
#include "include/sphere.h"
#include"include/common.h"
#include "include/camera.h"
#include "include/BVH.h"
#include <iostream>


//color ray_color(const ray& r, const hittable& world) {
//    hitrecord rec;
//    if(world.hit(r, interval(0, infinity), rec))
//    {
//        return 0.5 * (rec.normal + color(1,1,1));
//        //return {1,0,0};
//    }
//    vec3 unit_direction = unit_vec(r.dir());
//    auto a = 0.5 * (unit_direction.y() + 1.0);
//    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
//}

int main() {

//    // Image
//    auto aspect_ratio = 16.0/9.0;
//
//    int image_width = 400;
//    int image_height = static_cast<int>(image_width / aspect_ratio);
//
//    hittable_list world;
//    world.add(make_shared<sphere>(point3d(0,0,-1),0.5));
//    world.add(make_shared<sphere>(point3d(0, -100.5, -1),100));
//    auto focal_length = 1.0;
//    auto viewport_height = 2.0;
//    auto viewport_width = viewport_height * (static_cast<double>(image_width)/image_height);
//    auto camera_center = vec3(0,0,0);
//
//    auto viewport_u = vec3(viewport_width, 0, 0);
//    auto viewport_v = vec3(0, -viewport_height, 0);
//
//    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
//    auto pixel_delta_u = viewport_u / image_width;
//    auto pixel_delta_v = viewport_v / image_height;
//
//    // Calculate the location of the upper left pixel.
//    auto viewport_upper_left = camera_center - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
//    auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
//
//    // Render
//
//    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
//
//    for (int j = 0; j < image_height; ++j) {
//        for (int i = 0; i < image_width; ++i) {
//            auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
//            auto ray_direction = pixel_center - camera_center;
//            ray r(camera_center, ray_direction);
//
//            color pixel_color = ray_color(r, world);
//            write_color(std::cout, pixel_color);
//        }
//    }
    hittable_list world;
    auto ground_material = make_shared<lambertian>(color(0.5,0.5,0.5));
    world.add(make_shared<sphere>(point3d(0,-1000,0),1000, ground_material));

    for (int a = -2; a < 2; a++)
    {
        for (int b = -2; b < 2; b++)
        {
            auto choose_mat = random_double();
            point3d center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());
            if ((center - point3d(4,0.2,0)).norm() > 0.9)
            {
                shared_ptr<material> sphere_material;
                if (choose_mat < 0.8)
                {
                    auto albedo = color::random() * color::random();
                    sphere_material = make_shared<lambertian>(albedo);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                }else if(choose_mat < 0.95)
                {
                    auto albedo = color::random(0.5, 1);
                    auto fuzz = random_double(0, 0.5);
                    sphere_material = make_shared<metal>(albedo, fuzz);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                }else
                {
                    sphere_material = make_shared<dielectric>(1.5);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }
    auto material1 = make_shared<dielectric>(1.5);
    world.add(make_shared<sphere>(point3d(0,0.5,0),1.0, material1));
    auto material2 = make_shared<lambertian>(color(0.4,0.2,0.1));
    world.add(make_shared<sphere>(point3d(-4,1,0),1.0, material1));
    auto new_world = bvh_node(world);
    camera cam;
    cam.vfov = 20;
    cam.lookfrom = point3d(13,2,3);
    cam.lookat = point3d(0,0,0);
    cam.vup = vec3(0,1,0);
    cam.render(new_world);
}