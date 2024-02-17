//
// Created by 段剑 on 2024/2/7.
//

#ifndef PRJ1_CAMERA_H
#define PRJ1_CAMERA_H
#include"hittable.h"
#include"color.h"
#include"material.h"
class camera
{
public:
    void render(hittable& world) {
        initialize();
        std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
        for (int j = 0; j < image_height; ++j) {
            for (int i = 0; i < image_width; ++i) {
                auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
                color pixel_color(0,0,0);
                for (int sample = 0; sample < sample_perpixel; sample++)
                {
                    ray r = get_ray(i,j);
                    pixel_color += ray_color(r, maxdepth, world);
                }



                write_color(std::cout, pixel_color, sample_perpixel);

            }
        }
    }

    int image_height = 225;
    int image_width = 400;
    vec3 pixel_delta_u, pixel_delta_v;
    point3d center, pixel00_loc;
    int sample_perpixel = 100;
    int maxdepth = 50;
    double vfov = 45;
    point3d lookfrom = point3d(0,0,-1);
    point3d lookat = point3d(0,0,0);
    vec3 vup = vec3(0,1,0);
    vec3 u,v,w;
    void initialize()
    {
        auto focal_length = (lookfrom - lookat).norm();
        auto theta = deg2rad(vfov);
        auto h = tan(theta/2);
        auto viewport_height = 2 * h * focal_length;
        auto viewport_width = viewport_height * (static_cast<double>(image_width)/image_height);
        center = lookfrom;
        w = unit_vec(lookfrom - lookat);
        u = unit_vec(cross(vup, w));
        v = cross(w,u);

        auto viewport_u = viewport_width * u;
        auto viewport_v = viewport_height * (-v);

        // Calculate the horizontal and vertical delta vectors from pixel to pixel.
        pixel_delta_u = viewport_u / image_width;
        pixel_delta_v = viewport_v / image_height;

        // Calculate the location of the upper left pixel.
        auto viewport_upper_left = center
                                   - focal_length * w - viewport_u/2 - viewport_v/2;
        pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
    }
    color ray_color(const ray& r, int depth, const hittable& world) {
        hitrecord rec;
        if(depth <= 0)
            return color(0,0,0);
        if(world.hit(r, interval(0.001, infinity), rec))
        {
            ray scattered;
            color attenuation;
            if (rec.mat->scatter(r,rec,attenuation, scattered))
                return attenuation * ray_color(scattered, depth - 1, world);
            return color(0,0,0);
//            vec3 direction = rec.normal + random_unit_vec();
//            return 0.7 * ray_color(ray(rec.hit_point, direction), depth - 1, world);
        }
        vec3 unit_direction = unit_vec(r.dir());
        auto a = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
    }

    vec3 pixel_sample() const
    {
        auto px = -0.5 + random_double();
        auto py = -0.5 + random_double();
        return (px * pixel_delta_u) + (py * pixel_delta_v);
    }
    ray get_ray(int i, int j) const
    {
        auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
        auto sample_pixel = pixel_center + pixel_sample();
        auto direction = sample_pixel - center;
        return ray(center, direction);
    }



};
#endif //PRJ1_CAMERA_H
