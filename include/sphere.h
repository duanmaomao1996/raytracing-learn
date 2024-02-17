//
// Created by 段剑 on 2024/2/5.
//
#include"hittable.h"
#include "aabb.h"

#ifndef PRJ1_SPHERE_H
#define PRJ1_SPHERE_H
class sphere : public hittable
{
public:
    sphere(point3d _center, double _radius, shared_ptr<material> _material):center(_center), radius(_radius),
    mat(_material)
    {
        auto r_vec = vec3(radius, radius, radius);
        box = aabb(center - r_vec, center + r_vec);

    }
    bool hit(const ray& r, interval ray_t, hitrecord& rec) const
    {
        vec3 oc = r.orig() - center;
        double a = r.dir().norm_squared();
        double b = 2 * dot(r.dir(), oc);
        double c = oc.norm_squared() - radius *  radius;
        double discrim = b * b - 4 * a * c;
        if (discrim < 0)
            return false;
        auto root = (-b - sqrt(discrim)) / (2 * a);
        if (root <= ray_t.min() || ray_t.max() <= root)
        {
            root = (-b + sqrt(discrim)) / (2 * a);
            if (root <= ray_t.min() || ray_t.max() <= root)
                return false;
        }
        rec.t = root;
        rec.hit_point = r.at(rec.t);
        rec.normal = (rec.hit_point - center) / radius;
        vec3 outward_normal = (rec.hit_point - center) / radius;
        rec.mat = mat;
        return true;
    }
    aabb bounding_box() const override{return box;}
private:
    point3d center;
    double radius;
    shared_ptr<material> mat;
    aabb box;

};
#endif //PRJ1_SPHERE_H
