//
// Created by Minghao Guo on 2021/3/2.
//

#ifndef INCLUDE_REDUCE_H
#define INCLUDE_REDUCE_H
#include <thrust/device_vector.h>
#include <thrust/transform.h>
#include <thrust/functional.h>
#include <thrust/count.h>
#include <thrust/execution_policy.h>
#include "functor.h"

using namespace thrust;
using namespace thrust::placeholders;

template <typename T>
int count_eq(const device_vector<T> & vec, const T val = 1.f)
{
    return count_if(thrust::device, vec.begin(), vec.end(), eq_functor<T>(val));
}


#endif //INCLUDE_REDUCE_H
