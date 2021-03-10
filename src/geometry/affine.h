//
// Created by Minghao Guo on 2021/2/25.
//

#ifndef INCLUDE_AFFINE_H
#define INCLUDE_AFFINE_H
#pragma once
#include "../include/basic_types.h"

struct Affine
{
    Affine() {
        vec_float affine_ = vec_float(16);
        affine_[0] = 1.0f;
        affine_[5] = 1.0f;
        affine_[10] = 1.0f;
        this->data = affine_;
    }
    Affine(const vec_float data_): data(data_) {}
    Vector3D<float> GetSize() const
    {
        return Vector3D<float>(this->data[0], this->data[5], this->data[10]);
    }

    Vector3D<float> GetCenter() const
    {
        return Vector3D<float>(this->data[3], this->data[7], this->data[11]);
    }

    friend std::ostream& operator<< (std::ostream& os, Affine & affine)
    {
        for (int row = 0; row < 4; row++)
        {
            for (int col = 0; col < 4; col++)
            {
                os << affine.data[row * 4 + col] << " ";
            }
            if (row < 3)
                os << std::endl;
        }
        return os;
    }

    vec_float data;
};

#endif //INCLUDE_AFFINE_H
