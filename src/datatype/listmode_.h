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

using namespace thrust;
using namespace thrust::placeholders;

template <typename IndexType = unsigned short>
class Listmode {
public:
    Listmode(const int num_): num(num_)
    {
        if (num_ < 0)
        {
            fprintf (stderr, "num of listmode is set to negative in file '%s' in line %i.\n",\
                 __FILE__, __LINE__);
        }
        this->index1 = device_vector<IndexType>(num_);
        this->index2 = device_vector<IndexType>(num_);
        this->time_diff = device_vector<float>(0);
        this->data = device_vector<float>(0);
        this->table_z = device_vector<float>(0);
    }

    Listmode(const device_vector<IndexType> index1_,
             const device_vector<IndexType> index2_):
             index1(index1_), index2(index2_)
    {
        this->num = index1_.size();
        this->time_diff = device_vector<float>(0);
        this->data = device_vector<float>(0);
        this->table_z = device_vector<float>(0);
    }

    Listmode(const device_vector<IndexType> index1_,
             const device_vector<IndexType> index2_,
             const device_vector<float> time_diff_):
            index1(index1_), index2(index2_), time_diff(time_diff_)
    {
        this->num = index1_.size();
        this->data = device_vector<float>(0);
        this->table_z = device_vector<float>(0);
    }

    __host__ __device__
    device_vector<IndexType>* GetIndex1()
    {
        return &this->index1;
    }

    __host__ __device__
    IndexType GetIndex1(const int ind)
    {
        return this->index1[ind];
    }

    __host__ __device__
    device_vector<IndexType>* GetIndex2()
    {
        return &this->index2;
    }

    __host__ __device__
    IndexType GetIndex2(const int ind)
    {
        return this->index2[ind];
    }

    __host__ __device__
    device_vector<float>* GetTimeDiff()
    {
        return &this->time_diff;
    }

    __host__ __device__
    float GetTimeDiff(const int ind)
    {
        return this->time_diff[ind];
    }

    __host__ __device__
    device_vector<float>* GetData()
    {
        return &this->data;
    }

    __host__ __device__
    float GetData(const int ind)
    {
        return this->data[ind];
    }

    __host__ __device__
    device_vector<float>* GetTableZ()
    {
        return &this->table_z;
    }

    __host__ __device__
    float GetTableZ(const int ind)
    {
        if (this->table_z.size() == 0)
        {return 0.f;}
        else
        {return this->table_z[ind];}
    }

    __host__
    void InitialData(const float val = 1.f)
    {
        this->data.resize(this->num);
        thrust::fill(this->data.begin(), this->data.end(), val);
    }


private:
    int num;

    device_vector<IndexType> index1;
    device_vector<IndexType> index2;
    vec_float time_diff; // arrive time index2 - index1
    vec_float data;
    vec_float table_z;
};

#endif //INCLUDE_LISTMODE_H
