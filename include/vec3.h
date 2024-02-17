//
// Created by 段剑 on 2024/2/5.
//

#ifndef PRJ1_VEC3_H
#define PRJ1_VEC3_H
#include<iostream>
#include "common.h"

class vec3
{
public:
    vec3():e{0,0,0}{}
    vec3(double _x, double _y, double _z):e{_x, _y, _z}{}
    double x() const {return e[0];}
    double y() const {return e[1];}
    double z() const {return e[2];}
    double operator[](unsigned int i){return e[i];}
    vec3& operator*=(double t){ e[0]*=t;e[1]*=t;e[2]*=t; return *this;}
    vec3& operator+=(vec3 v){ e[0] +=v.x();e[1]+=v.y();e[2]+=v.z(); return *this;}
    vec3& operator/=(double t){ e[0]/=t;e[1]/=t;e[2]/=t; return *this;}
    double norm_squared(){return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];}
    double norm() {return std::sqrt(norm_squared());}
    static vec3 random(){return vec3(random_double(),random_double(),random_double());}
    static vec3 random(double min, double max)
    {return vec3(random_double(min, max),random_double(min, max),random_double(min, max));}

private:
    double e[3];

};


inline vec3 cross(const vec3& u, const vec3& v)
{
    return vec3(u.y() * v.z() - u.z() * v.y(),
                u.z() * v.x() - u.x() * v.z(),
                u.x() * v.y() - u.y() * v.x());
}
inline vec3 operator+(const vec3& v1, const vec3& v2)
{
    return {v1.x()+v2.x(),v1.y()+v2.y(),v1.z()+v2.z()};
}

inline vec3 operator-(const vec3& v1, const vec3& v2)
{
    return {v1.x() - v2.x(),v1.y() - v2.y(),v1.z() - v2.z()};
}
inline vec3 operator*(const vec3& v1, const vec3& v2)
{
    return {v1.x() * v2.x(),v1.y() * v2.y(),v1.z() * v2.z()};
}

inline vec3 operator*(const vec3& v, double t)
{
    return {v.x() * t, v.y() * t, v.z() * t};
}

inline vec3 operator*(double t, const vec3& v)
{
    return v * t;
}

inline vec3 operator/(vec3 v, double t)
{
    return {v.x() / t, v.y() / t, v.z() / t};
}
inline vec3 operator-(vec3 v)
{
    return {-v.x(), -v.y(), -v.z()};
}

inline std::ostream& operator<<(std::ostream& out, const vec3& v)
{
    return out << v.x() << ' ' << v.y() << ' ' << v.z();
}
inline vec3 unit_vec(vec3 v)
{
    return v / v.norm();
}
inline double dot(const vec3& v1, const vec3& v2)
{
    return v1.x() * v2.x() + v1.y() * v2.y() + v1.z() * v2.z();
}

inline vec3 random_in_unit_vec()
{
    while(true) {
        auto p = vec3::random(-1, 1);
        if (p.norm() < 1)
            return p;
    }
}
inline vec3 random_unit_vec()
{
    return unit_vec(random_in_unit_vec());
}
inline vec3 random_on_hemisphere(const vec3& normal)
{
    vec3 on_unit_sphere = random_in_unit_vec();
    if (dot(on_unit_sphere, normal) > 0)
        return on_unit_sphere;
    else
        return -on_unit_sphere;

}

vec3 reflect(const vec3& v, const vec3& n)
{
    return v - 2 * dot(v,n)*n;
}

vec3 refract(const vec3& uv, const vec3& n, double etai_over_etat)
{
    auto cos_theta = fmin(dot(-uv, n), 1.0);
    vec3 r_out_perp = etai_over_etat * (uv + cos_theta * n);
    vec3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.norm())) * n;
    return r_out_perp + r_out_parallel;
}
using point3d = vec3;
#endif //PRJ1_VEC3_H



