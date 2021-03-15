//
// Created by Minghao Guo on 2021/3/2.
//

#ifndef INCLUDE_COUNTER_H
#define INCLUDE_COUNTER_H
#include <thrust/device_vector.h>
#include <thrust/transform.h>
#include <thrust/functional.h>
#include <thrust/count.h>
#include "functor.h"
#include "arithmetic.h"

using namespace thrust;
using namespace thrust::placeholders;

template <typename T>
int count_eq(const device_vector<T> & vec, const T val = 0.f)
{
    return count_if(vec.begin(), vec.end(), eq_functor<T>(val));
}

template <typename T>
int count_gt(const device_vector<T> & vec, const T val = 0.f)
{
    return count_if(vec.begin(), vec.end(), gt_functor<T>(val));
}

template <typename T>
int count_lt(const device_vector<T> & vec, const T val = 0.f)
{
    return count_if(vec.begin(), vec.end(), lt_functor<T>(val));
}

template <typename T>
int count_ge(const device_vector<T> & vec, const T val = 0.f)
{
    return count_if(vec.begin(), vec.end(), ge_functor<T>(val));
}

template <typename T>
int count_le(const device_vector<T> & vec, const T val = 0.f)
{
    return count_if(vec.begin(), vec.end(), le_functor<T>(val));
}

template <typename T>
int count_eq(const device_vector<T> & vec, const device_vector<T> & vec2)
{
    device_vector<T> diff_vec = vec - vec2;
    return count_if(diff_vec.begin(), diff_vec.end(), eq_functor<T>(0.f));
}

template <typename T>
int count_gt(const device_vector<T> & vec, const device_vector<T> & vec2)
{
    device_vector<T> diff_vec = vec - vec2;
    return count_if(diff_vec.begin(), diff_vec.end(), gt_functor<T>(0.f));
}

template <typename T>
int count_lt(const device_vector<T> & vec, const device_vector<T> & vec2)
{
    device_vector<T> diff_vec = vec - vec2;
    return count_if(diff_vec.begin(), diff_vec.end(), lt_functor<T>(0.f));
}

template <typename T>
int count_ge(const device_vector<T> & vec, const device_vector<T> & vec2)
{
    device_vector<T> diff_vec = vec - vec2;
    return count_if(diff_vec.begin(), diff_vec.end(), ge_functor<T>(0.f));
}

template <typename T>
int count_le(const device_vector<T> & vec, const device_vector<T> & vec2)
{
    device_vector<T> diff_vec = vec - vec2;
    return count_if(diff_vec.begin(), diff_vec.end(), le_functor<T>(0.f));
}

#endif //INCLUDE_COUNTER_H
