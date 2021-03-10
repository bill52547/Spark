//
// Created by Minghao Guo on 2021/3/1.
//

#ifndef INCLUDE_COMPARISON_H
#define INCLUDE_COMPARISON_H
#include <thrust/device_vector.h>
#include <thrust/transform.h>
#include <thrust/functional.h>
#include "functor.h"

using namespace thrust;
using namespace thrust::placeholders;
template <typename T>
device_vector<T> operator> (const device_vector<T> & vec, const device_vector<T> & vec2)
{
    assert(vec.size() == vec2.size());
    device_vector<T> vec_out = device_vector<T>(vec.size());
    transform(vec.begin(), vec.end(),
              vec2.begin(),
              vec_out.begin(),
              gt2_functor<T>());
    return vec_out;
}

template <typename T, typename T2>
device_vector<T> operator> (const device_vector<T> & vec, const T2 & val)
{
    device_vector<T> vec_out = device_vector<T>(vec.size());
    transform(vec.begin(), vec.end(),
              vec_out.begin(),
              gt_functor<T>(val));
    return vec_out;
}

template <typename T, typename T2>
device_vector<T> operator> (const T2 & val, const device_vector<T> & vec)
{
    device_vector<T> vec_out = device_vector<T>(vec.size());
    transform(vec.begin(), vec.end(),
              vec_out.begin(),
              lt_functor<T>(val));
    return vec_out;
}

template <typename T>
device_vector<T> operator< (const device_vector<T> & vec, const device_vector<T> & vec2)
{
    assert(vec.size() == vec2.size());
    device_vector<T> vec_out = device_vector<T>(vec.size());
    transform(vec.begin(), vec.end(),
              vec2.begin(),
              vec_out.begin(),
              lt2_functor<T>());
    return vec_out;
}

template <typename T, typename T2>
device_vector<T> operator< (const device_vector<T> & vec, const T2 & val)
{
    device_vector<T> vec_out = device_vector<T>(vec.size());
    transform(vec.begin(), vec.end(),
              vec_out.begin(),
              lt_functor<T>(val));
    return vec_out;
}

template <typename T, typename T2>
device_vector<T> operator< (const T2 & val, const device_vector<T> & vec)
{
    device_vector<T> vec_out = device_vector<T>(vec.size());
    transform(vec.begin(), vec.end(),
              vec_out.begin(),
              gt_functor<T>(val));
    return vec_out;
}

// TODO
#endif //INCLUDE_COMPARISON_H
