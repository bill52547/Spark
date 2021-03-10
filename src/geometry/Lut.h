//
// Created by Minghao Guo on 2021/3/5.
//

#ifndef INCLUDE_LUT_H
#define INCLUDE_LUT_H
#pragma once
#include <thrust/device_vector.h>
#include <string>
#include <fstream>
#include <iostream>
#include "../include/rawdata_io.h"
#include "../config/filesystem.h"

using namespace thrust;
using namespace std;

class PosLutBoundary
{
public:
    device_vector<float> data;
public:
    PosLutBoundary(device_vector<float> & data_):data(data_){}

    static PosLutBoundary read_raw(string & path)
    {
        int num;
        std::ifstream FILE(path, std::ios::in | std::ifstream::binary);
        num = scalar_reader<int>(FILE);
        FILE.seekg(DATA_BYTE_SHIFT, std::ios::beg);
        device_vector<float> data_ = vector_reader<float>(FILE, num * 6);
        cout << data_.size() << endl;
        return PosLutBoundary(data_);
    }
};

#endif //INCLUDE_LUT_H
