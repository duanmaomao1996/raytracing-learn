//
// Created by 段剑 on 2024/2/5.
//
#include"hittable.h"

#include <utility>
#include<vector>
#include<memory>

using std::shared_ptr;
using std::make_shared;
#ifndef PRJ1_HITTABLE_LIST_H
#define PRJ1_HITTABLE_LIST_H
class hittable_list:public hittable
{


public:
    std::vector<shared_ptr<hittable>> objects;
    hittable_list(){}
    hittable_list(shared_ptr<hittable> object){add(object);}
    void add(shared_ptr<hittable> object)
    {
        objects.push_back(object);
        box = aabb(box, object->bounding_box());
    }
    void clear()
    {
        objects.clear();
    }
    bool hit(const ray& r, interval ray_t, hitrecord& rec) const override
    {
        bool is_hit = false;
        hitrecord temp_rec;
        auto closest = ray_t.max();
        for (auto& object:objects)
        {
            if (object->hit(r, interval(ray_t.min(),closest), temp_rec))
            {
                is_hit = true;
                closest = temp_rec.t;
                rec = temp_rec;
            }
        }
        return is_hit;
    }
    aabb bounding_box() const
    {
        return box;
    }
private:
    aabb box;
};

#endif //PRJ1_HITTABLE_LIST_H
