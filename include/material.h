//
// Created by 段剑 on 2024/2/12.
//

#ifndef PRJ1_MATERIAL_H
#define PRJ1_MATERIAL_H

#include"common.h"
#include "ray.h"
#include "hittable.h"
#include "color.h"

class material
{
public:
    virtual ~material() = default;
    virtual bool scatter(const ray& r_in, hitrecord& rec, color& attenuation, ray& scattered) const = 0;
};

class lambertian: public material
{
public:
    lambertian(const color& a): albedo(a) {}
    bool scatter(const ray& r, hitrecord& rec, color& attenuation, ray& scattered) const override
    {
        auto scatter_direction = rec.normal + random_unit_vec();
        scattered = ray(rec.hit_point, scatter_direction);
        attenuation = albedo;
        return true;
    }
private:
    color albedo;
};

class metal: public material
{
public:
    metal(const color& a, double f):albedo(a), fuzz(f<1?f:1){}
    bool scatter(const ray& r, hitrecord& rec, color& attenuation, ray& scattered) const override
    {
        vec3 reflected = reflect(unit_vec(r.dir()),rec.normal);
        scattered = ray(rec.hit_point, reflected + fuzz * random_unit_vec());
        attenuation = albedo;
        return true;
    }
private:
    color albedo;
    double fuzz;
};

class dielectric: public material
{
public:
    dielectric(double refraction):ir(refraction){}
    bool scatter(const ray& r, hitrecord& rec, color& attenuation, ray& scattered) const override
    {
        attenuation = color(1,1,1);
        double refraction_ratio = rec.front_face ? (1.0/ir):ir;
        vec3 unit_direction = unit_vec(r.dir());
        double cos_theta = fmin(dot(-unit_direction,rec.normal),1.0);
        double sin_theta = sqrt(1.0 - cos_theta * cos_theta);

        bool cannot_refract = refraction_ratio * sin_theta > 1.0;
        vec3 direction;
        if (cannot_refract || reflectance(cos_theta, refraction_ratio) > random_double())
            direction = reflect(unit_direction, rec.normal);
        else
            direction = refract(unit_direction, rec.normal, refraction_ratio);

        scattered  = ray(rec.hit_point, direction);
        return true;
    }
private:
    double ir;
    static double reflectance(double cosine, double ref_idx)
    {
        auto r0 = (1 - ref_idx) / (1 + ref_idx);
        r0 = r0 * r0;
        return r0 + (1 -r0)*pow((1-cosine),5);
    }
};
#endif //PRJ1_MATERIAL_H
