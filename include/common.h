//
// Created by 段剑 on 2024/2/5.
//

#ifndef PRJ1_COMMON_H
#define PRJ1_COMMON_H

#include<cmath>
#include<limits>
#include<memory>
const double infinity = std::numeric_limits<double>::infinity();
const double PI = 3.1415926653589;
using std::shared_ptr;
using std::make_shared;
using std::sqrt;
inline double deg2rad(double degree)
{
    return degree * PI / 180.0;
}

inline double random_double()
{
    return rand() / (RAND_MAX + 1.0);
}
inline double random_double(double min, double max)
{
    return min + (max - min) * random_double();
}
inline int random_int(int min, int max)
{
    return static_cast<int>(random_double(min, max+1));
}

#include "vec3.h"
#include "interval.h"
#endif //PRJ1_COMMON_H
