//
// Created by Minghao Guo on 2021/3/1.
//

#ifndef INCLUDE_RANDOM_GENERATOR_H
#define INCLUDE_RANDOM_GENERATOR_H
#include <thrust/random.h>
#include <thrust/device_vector.h>
#include <thrust/functional.h>
#include <thrust/iterator/counting_iterator.h>
#include <chrono>

using namespace thrust;
using namespace thrust::placeholders;

struct norm_rand
{
    float a, b;
    unsigned long t;
    __host__ __device__
    norm_rand(float _a=0.f, float _b=1.f, unsigned long _t = 0) : a(_a), b(_b), t(_t) {};

    __host__ __device__
    float operator()(const unsigned int n) const
    {
        thrust::default_random_engine rng;
        thrust::normal_distribution<float> dist(a, b);
        rng.discard(n + t);
        return dist(rng);
    }
};

template <typename T>
device_vector<T> normal_random(const int size, const float mean = 0.0f, const float std = 1.0f)
{
    const auto p1 = std::chrono::system_clock::now();
    const unsigned t = std::chrono::duration_cast<std::chrono::milliseconds>(
            p1.time_since_epoch()).count();
    device_vector<T> vec(size);
    thrust::counting_iterator<unsigned int> index_sequence_begin(0);
    thrust::transform(index_sequence_begin,
                      index_sequence_begin + size,
                      vec.begin(),
                      norm_rand(mean, std, t));
    return vec;
}
#endif //INCLUDE_RANDOM_GENERATOR_H
