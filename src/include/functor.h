//
// Created by Minghao Guo on 2021/3/2.
//

#ifndef INCLUDE_FUNCTOR_H
#define INCLUDE_FUNCTOR_H
#include <thrust/device_vector.h>
#include <thrust/transform.h>
#include <thrust/functional.h>
#include <cmath>
#include <iostream>
using namespace thrust;
using namespace thrust::placeholders;

template <typename T>
struct generator
{
    T a;
    generator(T a_): a(a_) {}
    __host__ __device__
    T operator() ()
    {
        return a;
    }
};

template<typename T>
struct gt_functor: public thrust::unary_function<T, T>
{
    T a;
    gt_functor(T a_): a(a_) {}
    __host__ __device__
    T operator() (T x)
    {
        if (x > a) {return 1.f;}
        else {return 0.f;}
    }
};

template<typename T>
struct gt2_functor: public thrust::binary_function<T, T, T>
{
    __host__ __device__
    T operator() (T x, T y)
    {
        if (x > y) {return 1.f;}
        else {return 0.f;}
    }
};

template<typename T>
struct lt_functor: public thrust::unary_function<T, T>
{
    T a;
    lt_functor(T a_): a(a_) {}
    __host__ __device__
    T operator() (T x)
    {
        if (x < a) {return 1.f;}
        else {return 0.f;}
    }
};

template<typename T>
struct lt2_functor: public thrust::binary_function<T, T, T>
{
    __host__ __device__
    T operator() (T x, T y)
    {
        if (x < y) {return 1.f;}
        else {return 0.f;}
    }
};

template<typename T>
struct ge_functor: public thrust::unary_function<T, T>
{
    T a;
    ge_functor(T a_): a(a_) {}
    __host__ __device__
    T operator() (T x)
    {
        if (x >= a) {return 1.f;}
        else {return 0.f;}
    }
};

template<typename T>
struct ge2_functor: public thrust::binary_function<T, T, T>
{
    __host__ __device__
    T operator() (T x, T y)
    {
        if (x >= y) {return 1.f;}
        else {return 0.f;}
    }
};

template<typename T>
struct le_functor: public thrust::unary_function<T, T>
{
    T a;
    le_functor(T a_): a(a_) {}
    __host__ __device__
    T operator() (T x)
    {
        if (x <= a) {return 1.f;}
        else {return 0.f;}
    }
};

template<typename T>
struct le2_functor: public thrust::binary_function<T, T, T>
{
    __host__ __device__
    T operator() (T x, T y)
    {
        if (x <= y) {return 1.f;}
        else {return 0.f;}
    }
};

template<typename T>
struct eq_functor: public thrust::unary_function<T, T>
{
    T a;
    eq_functor(T a_): a(a_) {}
    __host__ __device__
    T operator() (T x)
    {
        if (x == a) {return 1.f;}
        else {return 0.f;}
    }
};

template<typename T>
struct eq2_functor: public thrust::binary_function<T, T, T>
{
    __host__ __device__
    T operator() (T x, T y)
    {
        if (x == y) {return 1.f;}
        else {return 0.f;}
    }
};

template<typename T>
struct abs_functor: public thrust::unary_function<T, T>
{
    __host__ __device__
    T operator()(const T & z)
    {
        if (z >= 0.f) {return z;}
        else {return -z;}
    }
};

template <typename T>
struct pow_functor: public thrust::binary_function<T, T, T>
{
    T val;
    pow_functor(const T val_): val(val_) {}

    __host__ __device__
    T operator()(const T & z)
    {
        return std::pow(z, val);
    }
};

template <typename T>
struct exp_functor: public thrust::unary_function<T, T>
{
    __host__ __device__
    T operator()(const T & z)
    {
        return std::exp(z);
    }
};

template <typename T>
struct exp2_functor: public thrust::binary_function<T, T, T>
{
    T base;
    exp2_functor(const T base_ = 2): base(base_) {}

    __host__ __device__
    T operator()(const T & z)
    {
        return std::pow(base, z);
    }
};

template <typename T>
struct log_functor: public thrust::binary_function<T, T, T>
{
    T log_base;
    log_functor(const T base_ = 1): log_base(std::log(base_)) {}

    __host__ __device__
    T operator()(const T & z)
    {
        if (log_base == 0)
            return std::log(z);
        else
            return std::log(z) / log_base;
    }
};

template <typename T>
struct true_divide_functor: public thrust::binary_function<T, T, T>
{
    T divider;
    T _default;
    true_divide_functor(const T divider_ = 1, const T default_ = 0):
    divider(divider_),
    _default(default_)
    {
        if (divider_ == 0)
        {
            fprintf (stderr, "Divider is set to 0 in file '%s' in line %i.\n",\
                 __FILE__, __LINE__);
        }
    }

    __host__ __device__
    T operator()(const T & z)
    {
        return z / divider;
    }

    __host__ __device__
    T operator()(const T & z1, const T & z2)
    {
        return z1 / z2;
    }
};

#endif //INCLUDE_FUNCTOR_H
