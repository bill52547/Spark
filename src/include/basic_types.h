//
// Created by Minghao Guo on 2021/2/25.
//

#ifndef INCLUDE_BASIC_TYPES_H
#define INCLUDE_BASIC_TYPES_H
#pragma once

#include <thrust/device_vector.h>
#include <iostream>

using vec_float = thrust::device_vector<float>;
using vec_int = thrust::device_vector<int>;
using vec_ushort= thrust::device_vector<unsigned short>;
using vec_size_t = thrust::device_vector<size_t>;

template <typename T>
struct Vector3D
{

    Vector3D()
    {
        this->x = static_cast<T>(0);
        this->y = static_cast<T>(0);
        this->z = static_cast<T>(0);
    }

    Vector3D(T x_, T y_, T z_):
            x(x_), y(y_), z(z_)
    {
    }

    friend std::ostream& operator<< (std::ostream& os, Vector3D & vec)
    {
        os << vec.x << " " << vec.y << " " << vec.z;
        return os;
    }

    T x;
    T y;
    T z;
};

using Shape = Vector3D<int>;


#endif //INCLUDE_BASIC_TYPES_H
