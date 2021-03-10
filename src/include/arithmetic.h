//
// Created by Minghao Guo on 2021/3/1.
//

#ifndef INCLUDE_ARITHMETIC_H
#define INCLUDE_ARITHMETIC_H
#include <thrust/device_vector.h>
#include <thrust/transform.h>
#include <thrust/functional.h>
#include <thrust/fill.h>

using namespace thrust;
using namespace thrust::placeholders;

template <typename T>
device_vector<T> operator+ (const device_vector<T> & vec, const device_vector<T> & vec2)
{
    assert(vec.size() == vec2.size());
    device_vector<T> vec_out = device_vector<T>(vec.size());
    thrust::transform(vec.begin(), vec.end(),
              vec2.begin(),
              vec_out.begin(),
              _1 + _2);
    return vec_out;
}

template <typename T, typename T2>
device_vector<T> operator+ (const device_vector<T> & vec, const T2 & val)
{
    device_vector<T> vec_out = device_vector<T>(vec.size());
    thrust::transform(vec.begin(), vec.end(),
              vec_out.begin(),
              _1 + val);
    return vec_out;
}

template <typename T, typename T2>
device_vector<T> operator+ (const T2 & val, const device_vector<T> & vec)
{
    device_vector<T> vec_out = device_vector<T>(vec.size());
    thrust::transform(vec.begin(), vec.end(),
              vec_out.begin(),
              _1 + val);
    return vec_out;
}

template <typename T>
device_vector<T> operator- (const device_vector<T> & vec)
{
    device_vector<T> vec_out = device_vector<T>(vec.size());
    thrust::transform(vec.begin(), vec.end(),
              vec_out.begin(),
              -_1);
    return vec_out;
}

template <typename T>
device_vector<T> operator- (const device_vector<T> & vec, const device_vector<T> & vec2)
{
    assert(vec.size() == vec2.size());
    device_vector<T> vec_out = device_vector<T>(vec.size());
    thrust::transform(vec.begin(), vec.end(),
              vec2.begin(),
              vec_out.begin(),
              _1 - _2);
    return vec_out;
}

template <typename T, typename T2>
device_vector<T> operator- (const device_vector<T> & vec, const T2 & val)
{
    device_vector<T> vec_out = device_vector<T>(vec.size());
    thrust::transform(vec.begin(), vec.end(),
              vec_out.begin(),
              _1 - val);
    return vec_out;
}

template <typename T, typename T2>
device_vector<T> operator- (const T2 & val, const device_vector<T> & vec)
{
    device_vector<T> vec_out = device_vector<T>(vec.size());
    thrust::transform(vec.begin(), vec.end(),
              vec_out.begin(),
              val - _1);
    return vec_out;
}

template <typename T>
device_vector<T> operator* (const device_vector<T> & vec, const device_vector<T> & vec2)
{
    assert(vec.size() == vec2.size());
    device_vector<T> vec_out = device_vector<T>(vec.size());
    thrust::transform(vec.begin(), vec.end(),
              vec2.begin(),
              vec_out.begin(),
              _1 * _2);
    return vec_out;
}

template <typename T, typename T2>
device_vector<T> operator* (const device_vector<T> & vec, const T2 & val)
{
    device_vector<T> vec_out = device_vector<T>(vec.size());
    thrust::transform(vec.begin(), vec.end(),
              vec_out.begin(),
              _1 * val);
    return vec_out;
}

template <typename T, typename T2>
device_vector<T> operator* (const T2 & val, const device_vector<T> & vec)
{
    device_vector<T> vec_out = device_vector<T>(vec.size());
    thrust::transform(vec.begin(), vec.end(),
              vec_out.begin(),
              val * _1);
    return vec_out;
}

template <typename T>
device_vector<T> operator/ (const device_vector<T> & vec, const device_vector<T> & vec2)
{
    assert(vec.size() == vec2.size());
    device_vector<T> vec_out = device_vector<T>(vec.size());
    thrust::transform(vec.begin(), vec.end(),
              vec2.begin(),
              vec_out.begin(),
              _1 / _2);
    return vec_out;
}

template <typename T, typename T2>
device_vector<T> operator/ (const device_vector<T> & vec, const T2 & val)
{
    device_vector<T> vec_out = device_vector<T>(vec.size());
    thrust::transform(vec.begin(), vec.end(),
              vec_out.begin(),
              _1 / val);
    return vec_out;
}

template <typename T, typename T2>
device_vector<T> operator/ (const T2 & val, const device_vector<T> & vec)
{
    device_vector<T> vec_out = device_vector<T>(vec.size());
    thrust::transform(vec.begin(), vec.end(),
              vec_out.begin(),
              val / _1);
    return vec_out;
}

template <typename T>
device_vector<T> operator% (const device_vector<T> & vec, const device_vector<T> & vec2)
{
    assert(vec.size() == vec2.size());
    device_vector<T> vec_out = device_vector<T>(vec.size());
    thrust::transform(vec.begin(), vec.end(),
              vec2.begin(),
              vec_out.begin(),
              modulus<T>());
    return vec_out;
}

template <typename T>
device_vector<T> operator% (const device_vector<T> & vec, const T & val)
{
    device_vector<T> vec_out = device_vector<T>(vec.size());
    thrust::transform(vec.begin(), vec.end(),
              vec_out.begin(),
              _1 % val);
    return vec_out;
}

template <typename T>
device_vector<T> operator% (const T & val, const device_vector<T> & vec)
{
    device_vector<T> vec_out = device_vector<T>(vec.size());
    thrust::transform(vec.begin(), vec.end(),
              vec_out.begin(),
              val % _1);
    return vec_out;
}

#include "functor.h"

template <typename T>
device_vector<T> true_div(const device_vector<T> & vec, const device_vector<T> & val)
{
    device_vector<T> vec_out = device_vector<T>(vec.size());
    thrust::transform(vec.begin(), vec.end(),
              vec_out.begin(),
              true_divide_functor<T>());
    return vec_out;
}


template <typename T>
device_vector<T> absolute(const device_vector<T> & vec)
{
    device_vector<T> vec_out = device_vector<T>(vec.size());
    thrust::transform(vec.begin(), vec.end(),
              vec_out.begin(),
              abs_functor<T>());
    return vec_out;
}

template <typename T>
device_vector<T> pow(const device_vector<T> & vec, const T val)
{
    device_vector<T> vec_out = device_vector<T>(vec.size());
    thrust::transform(vec.begin(), vec.end(),
              vec_out.begin(),
              pow_functor<T>(val));
    return vec_out;
}

template <typename T>
device_vector<T> exp(const device_vector<T> & vec)
{
    device_vector<T> vec_out = device_vector<T>(vec.size());
    thrust::transform(vec.begin(), vec.end(),
              vec_out.begin(),
              exp_functor<T>());
    return vec_out;
}

template <typename T>
device_vector<T> exp2(const device_vector<T> & vec, const T base)
{
    device_vector<T> vec_out = device_vector<T>(vec.size());
    thrust::transform(vec.begin(), vec.end(),
              vec_out.begin(),
              exp2_functor<T>(base));
    return vec_out;
}

template <typename T>
device_vector<T> log(const device_vector<T> & vec, const T base = 1)
{
    device_vector<T> vec_out = device_vector<T>(vec.size());
    thrust::transform(vec.begin(), vec.end(),
              vec_out.begin(),
              log_functor<T>(base));
    return vec_out;
}

#endif //INCLUDE_ARITHMETIC_H
