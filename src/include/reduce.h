//
// Created by Minghao Guo on 2021/3/2.
//

#ifndef INCLUDE_REDUCE_H
#define INCLUDE_REDUCE_H
#include <thrust/device_vector.h>
#include <thrust/transform.h>
#include <thrust/functional.h>
#include <thrust/count.h>
#include <thrust/reduce.h>
#include <thrust/transform_reduce.h>
#include <cmath>
#include "functor.h"

template <typename T>
T maximum(thrust::device_vector<T> & vec, const T default_)
{
    return thrust::reduce(vec.begin(),
                          vec.end(),
                          default_,
                          thrust::maximum<T>());
}

template <typename T>
T minimum(thrust::device_vector<T> & vec, const T default_)
{
    return thrust::reduce(vec.begin(),
                          vec.end(),
                          default_,
                          thrust::minimum<T>());
}

template <typename T>
T summation(thrust::device_vector<T> & vec)
{
    return thrust::reduce(vec.begin(),
                          vec.end());
}

int count_true(thrust::device_vector<bool> & vec)
{
    return thrust::reduce(vec.begin(),
                          vec.end());
}

template <typename T>
T norm2(thrust::device_vector<T> & vec)
{
    square<T> unary_op;
    thrust::plus<T> binary_op;
    float out = std::sqrt(thrust::transform_reduce(vec.begin(), vec.end(), unary_op, 0.f, binary_op));

    return out;
}

template <typename T>
T norm1(thrust::device_vector<T> & vec)
{
    abs_functor<T> unary_op;
    thrust::plus<T> binary_op;
    float out = thrust::transform_reduce(vec.begin(), vec.end(), unary_op, 0.f, binary_op);

    return out;
}

template <typename T>
T norm(thrust::device_vector<T> & vec, const T val)
{
    pow_functor<T> pow_op(val);
    thrust::plus<T> binary_op;
    float out = thrust::transform_reduce(vec.begin(), vec.end(), pow_op, 0.f, binary_op);
    return out;
}

#endif //INCLUDE_REDUCE_H
