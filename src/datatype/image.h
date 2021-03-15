//
// Created by Minghao Guo on 2021/2/25.
//

#ifndef INCLUDE_IMAGE_H
#define INCLUDE_IMAGE_H
#pragma once

#include <thrust/device_vector.h>
#include <thrust/transform.h>
#include <thrust/functional.h>
#include <string>
#include <fstream>
#include <iostream>

#include "../include/basic_types.h"
#include "../geometry/affine.h"
#include "../include/common.h"


using namespace thrust;
using namespace thrust::placeholders;

class Image
{
public:
    using ThisClass=Image;
    Image(const Shape shape_, const Affine affine_ = Affine(), const float value_ = 0.0f):
            shape(shape_),
            affine(affine_)
    {
        this->data.resize(shape_.x * shape_.y * shape_.z);
        thrust::fill(this->data.begin(), this->data.end(), value_);
    }

    Image(const Shape shape_, const Affine affine_, const vec_float data_):
    shape(shape_),
    affine(affine_),
    data(data_)
    {
    }

    Image UpdateData(vec_float data_)
    {
        return Image(this->shape, this->affine, data_);
    }

    Shape GetShape() const
    {
        return this->shape;
    }

    Affine GetAffine() const
    {
        return this->affine;
    }

    vec_float GetData() const
    {
        return this->data;
    }

    __host__
    float* GetDataRawPtr()
    {
        return thrust::raw_pointer_cast(this->data.data());
    }

    Vector3D<float> GetCenter() const
    {
        return this->affine.GetCenter();
    }

    Vector3D<float> GetSize() const
    {
        return this->affine.GetSize();
    }

    Vector3D<float> GetUnitSize() const
    {
        auto size_ = this->affine.GetSize();
        auto shape_ = this->shape;
        return Vector3D<float>(size_.x / shape_.x, size_.y / shape_.y, size_.z / shape_.z);
    }

    unsigned long GetDataNumber() const
    {
        return this->shape.x * this->shape.y * this->shape.z;
    }

    unsigned long GetDataCapacity() const
    {
        return this->GetDataNumber() * sizeof(float);
    }

    ThisClass operator+ (const float v);
    ThisClass operator- (const float v);
    ThisClass operator* (const float v);
    ThisClass operator/ (const float v);
    ThisClass operator% (const float v);
    ThisClass operator> (const float v);
    ThisClass operator< (const float v);
    ThisClass operator>= (const float v);
    ThisClass operator<= (const float v);
    ThisClass operator== (const float v);

    ThisClass operator+ (const ThisClass & v);
    ThisClass operator- (const ThisClass & v);
    ThisClass operator* (const ThisClass & v);
    ThisClass operator/ (const ThisClass & v);
    ThisClass operator% (const ThisClass & v);
    ThisClass operator> (const ThisClass & v);
    ThisClass operator< (const ThisClass & v);
    ThisClass operator>= (const ThisClass & v);
    ThisClass operator<= (const ThisClass & v);
    ThisClass operator== (const ThisClass & v);

    friend ThisClass operator+ (const float v, ThisClass & other);
    friend ThisClass operator- (const float v, ThisClass & other);
    friend ThisClass operator* (const float v, ThisClass & other);
    friend ThisClass operator/ (const float v, ThisClass & other);
    friend ThisClass operator% (const float v, ThisClass & other);
    friend ThisClass operator> (const float v, ThisClass & other);
    friend ThisClass operator< (const float v, ThisClass & other);
    friend ThisClass operator>= (const float v, ThisClass & other);
    friend ThisClass operator<= (const float v, ThisClass & other);
    friend ThisClass operator== (const float v, ThisClass & other);


    void write(std::string & path) const;
    static Image read(std::string & path);

    void write_json(const std::string & filename) const;
    static Image read_json(const std::string & filename);

private:
    Shape shape;
    Affine affine;
    thrust::device_vector<float> data;
};


#endif //INCLUDE_IMAGE_H
