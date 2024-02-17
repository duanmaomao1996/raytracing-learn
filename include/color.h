//
// Created by 段剑 on 2024/2/5.
//

#ifndef PRJ1_COLOR_H
#define PRJ1_COLOR_H
#include"vec3.h"

using color = vec3;

void write_color(std::ostream& out, color pixel_color, int samples_per_pixel)
{
    out << static_cast<int>(255.99 * pixel_color.x()) / samples_per_pixel<< ' '
        << static_cast<int>(255.99 * pixel_color.y()) / samples_per_pixel<< ' '
        << static_cast<int>(255.99 * pixel_color.z()) /samples_per_pixel<< '\n';
}
#endif //PRJ1_COLOR_H
