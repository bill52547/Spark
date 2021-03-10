//
// Created by Minghao Guo on 2021/3/1.
//

#ifndef INCLUDE_LISTMODE_H
#define INCLUDE_LISTMODE_H
#pragma once
#include <thrust/device_vector.h>
#include "../include/basic_types.h"
#include "../include/constants.h"
#include <thrust/transform.h>
#include "../config/config.h"
#include "LineOfResponse.h"
using namespace thrust;
using namespace thrust::placeholders;

class Listmode {
public:
    LineOfResponse lors;
    device_vector<float> data = device_vector<float>(0);

public:
    Listmode(const LineOfResponse & lors_, const float default_value = 1.f):
    lors(lors_)
    {
        this->data.resize(lors_.GetNum());
        thrust::fill(this->data.begin(), this->data.end(), default_value);
    }

    Listmode(const LineOfResponse & lors_, const device_vector<float> & data_):
            lors(lors_), data(data_)
    {
        assert(lors_.GetNum() == data_.size());
    }

    int GetNum() const
    {
        return this->lors.GetNum();
    }

    __host__
    void SetData(const device_vector<float> data_)
    {
        if (this->data.size() == 0)
        {
            this->data.resize(this->GetNum());
        }
        this->data = data_;
    }

    __host__
    LineOfResponse& GetLOR()
    {
        return this->lors;
    }
    __host__
    device_vector<float>& GetData()
    {
        return this->data;
    }

    __host__
    float * GetDataRawPtr()
    {
        return thrust::raw_pointer_cast(this->data.data());
    }

    __host__
    IndexType * GetIndex1RawPtr()
    {
        return this->lors.GetIndex1RawPtr();
    }

    __host__
    IndexType * GetIndex2RawPtr()
    {
        return this->lors.GetIndex2RawPtr();
    }

    __host__
    float * GetTimeDiffRawPtr()
    {
        return this->lors.GetTimeDiffRawPtr();
    }

    __host__
    float * GetLutPosRawPtr()
    {
        return this->lors.GetLutPosRawPtr();
    }

    __host__ __device__
    float GetData(const int ind)
    {
        if (this->data.size() == 0)
        {return 0.f;}
        else
        {return this->data[ind];}
    }

    Listmode UpdateData(vec_float data_)
    {
        return Listmode(this->lors, data_);
    }

    Listmode operator+ (const float v);
    Listmode operator- (const float v);
    Listmode operator* (const float v);
    Listmode operator/ (const float v);

    Listmode operator+ (Listmode & v);
    Listmode operator- (Listmode & v);
    Listmode operator* (Listmode & v);
    Listmode operator/ (Listmode & v);
    Listmode true_div (Listmode & v);

    friend Listmode operator+ (const float v, Listmode & other);
    friend Listmode operator- (const float v, Listmode & other);
    friend Listmode operator* (const float v, Listmode & other);
    friend Listmode operator/ (const float v, Listmode & other);
};

#endif //INCLUDE_LISTMODE_H
