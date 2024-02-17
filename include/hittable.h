//
// Created by 段剑 on 2024/2/5.
//
#include "ray.h"
#include "interval.h"
#include "aabb.h"

#ifndef PRJ1_HITTABLE_H
#define PRJ1_HITTABLE_H

class material;

class hitrecord
{
public:
    point3d hit_point;
    bool is_hit;
    double t;
    vec3 normal;
    shared_ptr<material> mat;
    bool front_face;
    void set_face_normal(const ray& r, const vec3& outward_normal)
    {
        front_face = dot(r.dir(), outward_normal) < 0;
        normal = front_face ? outward_normal: -outward_normal;
    }
};

class hittable
{
public:
    virtual ~hittable() = default;
    virtual bool hit(const ray& r, interval ray_t, hitrecord& rec) const = 0;
    virtual aabb bounding_box() const = 0;
};
#endif //PRJ1_HITTABLE_H
