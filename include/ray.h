//
// Created by 段剑 on 2024/2/5.
//

#ifndef PRJ1_RAY_H
#define PRJ1_RAY_H

#include "vec3.h"

class ray
{
public:
    ray(){}
    ray(const point3d& _origin, const vec3& _direction):origin(_origin),direction(_direction){}
    point3d orig() const{return origin;}
    vec3   dir() const{return direction;}
    point3d at(double t) const{return origin + direction * t;}
private:
    point3d origin;
    vec3 direction;
};
#endif //PRJ1_RAY_H
