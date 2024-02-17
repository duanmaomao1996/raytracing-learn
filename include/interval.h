//
// Created by 段剑 on 2024/2/5.
//

#ifndef PRJ1_INTERVAL_H
#define PRJ1_INTERVAL_H
#include"common.h"
class interval
{
public:
    interval():tmin(+infinity),tmax(-infinity){}
    interval(double _min, double _max):tmin(_min),tmax(_max){}
    interval(const interval& a, const interval& b):tmin(fmin(a.tmin,b.tmin)),tmax(fmax(a.tmax,b.tmax)){}
    double max() const
    {
        return tmax;
    }
    double min() const
    {
        return tmin;
    }
    bool contains(double x) const
    {
        return tmin <= x && x <= tmax;
    }
    static const interval empty, universe;
    double tmin, tmax;
};

const static interval empty (+infinity, -infinity);
const static interval universe(-infinity, +infinity);
#endif //PRJ1_INTERVAL_H
