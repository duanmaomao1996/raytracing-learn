//
// Created by 段剑 on 2024/2/11.
//

#ifndef PRJ1_BVH_H
#define PRJ1_BVH_H

#include "hittable.h"
#include "hittable_list.h"

#include<algorithm>
class bvh_node: public hittable
{
public:
    explicit bvh_node(const hittable_list& list):bvh_node(list.objects, 0, list.objects.size()){}
    bvh_node(const std::vector<shared_ptr<hittable>>& src_objects, unsigned int start, unsigned int end)
    {
        auto objects = src_objects;
        int axis = random_int(0,2);
        auto comparator = (axis == 0) ? box_compare_x:(axis == 1)
                ? box_compare_y: box_compare_z;
        unsigned int span = end - start;
        if(span == 1)
            left = right = objects[start];
        else if (span == 2)
        {
            if (comparator(objects[start],objects[start+1]))
            {
                left = objects[start];
                right = objects[start+1];
            }
            else
            {
                left = objects[start+1];
                right = objects[start];
            }
        }
        else
        {
            std::sort(objects.begin() + start, objects.begin() + end, comparator);
            auto mid = start + span / 2;
            left = make_shared<bvh_node>(objects, start, mid);
            right = make_shared<bvh_node>(objects, mid, end);
        }
        box = aabb(left->bounding_box(), right->bounding_box());
    }
    bool hit(const ray& r, interval ray_t, hitrecord& rec)const override
    {
        if(box.hit(r,ray_t))
        {
            hitrecord left_record, right_record;
            bool left_hit = left->hit(r,ray_t,left_record);
            bool right_hit = right->hit(r, ray_t, right_record);
            if(left_hit && right_hit)
            {
                if (left_record.t < right_record.t)
                    rec = left_record;
                else
                    rec = right_record;
                return true;
            }
            else if(left_hit)
            {
                rec = left_record;
                return true;
            }
            else if(right_hit)
            {
                rec = right_record;
                return true;
            }
            return false;

        }
        else
            return false;
    }

    aabb bounding_box()const override{return box;}



private:
    shared_ptr<hittable> left;
    shared_ptr<hittable> right;
    aabb box;
    static bool box_compare(const shared_ptr<hittable> a, const shared_ptr<hittable> b, unsigned int index)
    {
        return a->bounding_box().axis(index).min() < b->bounding_box().axis(index).min();

    }
    static bool box_compare_x(const shared_ptr<hittable> a, const shared_ptr<hittable> b)
    {
        return box_compare(a,b,0);
    }

    static bool box_compare_y(const shared_ptr<hittable> a, const shared_ptr<hittable> b)
    {
        return box_compare(a,b,1);;
    }

    static bool box_compare_z(const shared_ptr<hittable> a, const shared_ptr<hittable> b)
    {
        return box_compare(a,b,2);
    }



};
#endif //PRJ1_BVH_H
