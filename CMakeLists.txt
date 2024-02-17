cmake_minimum_required(VERSION 3.27)
project(prj1)

set(CMAKE_CXX_STANDARD 17)

add_executable(prj1 main.cpp
        include/vec3.h
        include/color.h
        include/hittable.h
        include/sphere.h
        include/common.h
        include/hittable_list.h
        include/interval.h
        include/aabb.h
        include/camera.h
        include/ray.h
        include/BVH.h
        include/BVH.h
        include/material.h)
