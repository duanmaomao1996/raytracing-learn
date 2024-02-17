//
// Created by 段剑 on 2024/2/5.
//

#ifndef PRJ1_AABB_H
#define PRJ1_AABB_H
#include"common.h"
#include "ray.h"

class aabb
{
public:
    interval x, y, z;
    aabb() {}
    aabb(const interval& ix, const interval& iy, const interval& iz):x(ix),y(iy),z(iz) {}
    aabb(const point3d& p1, const point3d& p2)
    {
        x = interval(fmin(p1.x(), p2.x()), fmax(p1.x(), p2.x()));
        y = interval(fmin(p1.y(), p2.y()), fmax(p1.y(), p2.y()));
        z = interval(fmin(p1.z(), p2.z()), fmax(p1.z(), p2.z()));
    }
    aabb(const aabb& a, const aabb& b)
    {
        x = interval(a.x, b.x);
        y = interval(a.y, b.y);
        z = interval(a.z, b.z);
    }
    const interval& axis(int n) const
    {
        if (n == 1) return y;
        if (n == 2) return z;
        return x;
    }
    bool hit(const ray& r, interval ray_t) const
    {
        for (int i = 0; i < 3; i++)
        {
            double inv_d = 1 / r.dir()[i];
            double orig = r.orig()[i];
            double t0 = (axis(i).min() - orig) * inv_d;
            double t1 = (axis(i).max() - orig) * inv_d;
            if (inv_d < 0)
                std::swap(t0, t1);
            if (t0 > ray_t.min()) ray_t.tmin = t0;
            if (t1 < ray_t.max()) ray_t.tmax = t1;
            if (ray_t.tmin > ray_t.tmax) return false;
        }
        return true;
    }
};
#endif //PRJ1_AABB_H
