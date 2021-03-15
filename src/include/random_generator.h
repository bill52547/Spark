//
// Created by Minghao Guo on 2021/3/1.
//

#ifndef INCLUDE_RANDOM_GENERATOR_H
#define INCLUDE_RANDOM_GENERATOR_H
#include <thrust/random.h>
#include <thrust/device_vector.h>
#include <thrust/functional.h>
#include <thrust/iterator/counting_iterator.h>

using namespace thrust;
using namespace thrust::placeholders;

struct norm_rand
{
    float a, b;

    __host__ __device__
    norm_rand(float _a=0.f, float _b=1.f) : a(_a), b(_b) {};

    __host__ __device__
    float operator()(const unsigned int n) const
    {
        thrust::default_random_engine rng;
        thrust::normal_distribution<float> dist(a, b);
        rng.discard(n);
        return dist(rng);
    }
};

template <typename T>
device_vector<T> normal_random(const int size, const float mean = 0.0f, const float std = 1.0f)
{
    device_vector<T> vec(size);
    thrust::counting_iterator<unsigned int> index_sequence_begin(0);
    thrust::transform(index_sequence_begin,
                      index_sequence_begin + size,
                      vec.begin(),
                      norm_rand(mean, std));
    return vec;
}
#endif //INCLUDE_RANDOM_GENERATOR_H
