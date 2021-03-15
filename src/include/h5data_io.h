//
// Created by Minghao Guo on 2021/3/15.
//

#ifndef INCLUDE_H5DATA_IO_H
#define INCLUDE_H5DATA_IO_H
#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <highfive/H5File.hpp>
#include <highfive/H5DataType.hpp>
using namespace HighFive;
using namespace std;

template <typename T>
void vector_writer(const string & filename, const string & group_name, const std::vector<T> & vec)
{
    File file(filename, File::ReadWrite | File::Create | File::Truncate);
    Group group = file.createGroup(group_name);

    auto host_vec = std::vector<T>(vec.size());
    thrust::copy(vec.begin(), vec.end(), host_vec.begin());
    FILE.write(reinterpret_cast<const char *>(&host_vec[0]), vec.size() * sizeof(T));
}

#endif //INCLUDE_H5DATA_IO_H
