//
// Created by Minghao Guo on 2021/3/1.
//

#ifndef INCLUDE_RAWDATA_IO_H
#define INCLUDE_RAWDATA_IO_H
#include <thrust/device_vector.h>
#include <vector>
#include <fstream>
#include <thrust/copy.h>
#include <iostream>


template <typename T>
void scalar_writer(std::ofstream &FILE, const T val)
{
    FILE.write(reinterpret_cast<const char*>(&val), sizeof(T));
}

template <typename T>
T scalar_reader(std::ifstream &FILE)
{
    T val;
    FILE.read(reinterpret_cast<char*>(&val), sizeof(T));
    return val;
}

template <typename T>
void vector_writer(std::ofstream &FILE, const thrust::device_vector<T> & vec)
{
    auto host_vec = std::vector<T>(vec.size());
    thrust::copy(vec.begin(), vec.end(), host_vec.begin());
    FILE.write(reinterpret_cast<const char *>(&host_vec[0]), vec.size() * sizeof(T));
}

template <typename T>
thrust::device_vector<T> vector_reader(std::ifstream &FILE, const int size)
{
    auto host_vec = std::vector<T>(size);
    for (int i = 0; i < size; ++i)
    {
        T f_;
        FILE.read(reinterpret_cast<char *>(&f_), sizeof(T));
        host_vec[i] = f_;
    }
    auto out_vec = thrust::device_vector<T>(host_vec);

    return out_vec;
}

#endif //INCLUDE_RAWDATA_IO_H
