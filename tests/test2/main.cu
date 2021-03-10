//
// Created by Minghao Guo on 2021/2/25.
//

#include <thrust/device_vector.h>
#include "../../src/datatype/image.h"
#include "../../src/include/basic_types.h"
#include "../../src/geometry/affine.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

int main()
{
    std::string path = "./test.bin";
    std::ofstream FILE(path, std::ios::out | std::ofstream::binary);
    int nx = 1, ny = 2, nz = 3;
    FILE.seekp(0, std::ios::beg);
    FILE.write(reinterpret_cast<const char *>(&nx), 1 * sizeof(int));
    FILE.seekp(4, std::ios::beg);
    FILE.write(reinterpret_cast<const char *>(&ny), 1 * sizeof(int));
    FILE.seekp(8, std::ios::beg);
    FILE.write(reinterpret_cast<const char *>(&nz), 1 * sizeof(int));
    std::vector<int> vec = std::vector<int>(10);
    std::iota(vec.begin(), vec.end(), -3);

    FILE.seekp(256, std::ios::beg);
    FILE.write(reinterpret_cast<const char *>(&vec[0]), 10 * sizeof(int));
    FILE.close();

    int nx2 = 0, ny2 = 0, nz2 = 0;
    std::ifstream FILE2(path, std::ios::in | std::ifstream::binary);
    FILE2.seekg(0, std::ios::beg);
//    FILE2.read(reinterpret_cast<char *>(&nx2), 1 * sizeof(int));
    FILE2.read(reinterpret_cast<char *>(&nx2), 1 * sizeof(int));
    FILE2.seekg(4, std::ios::beg);
    FILE2.read(reinterpret_cast<char *>(&ny2), 1 * sizeof(int));
    FILE2.seekg(8, std::ios::beg);
    FILE2.read(reinterpret_cast<char *>(&nz2), 1 * sizeof(int));

    FILE2.seekg(256, std::ios::beg);
    std::vector<int> vec2 = std::vector<int>(10);
    for (int k = 0; k < 10; ++k)
    {
        int f;
        FILE2.read(reinterpret_cast<char *>(&f), sizeof(f));
        vec2[k] = f;
    }
//    FILE2.read(reinterpret_cast<char *>(&vec2.begin()), 10 * sizeof(int));
    std::cout << nx2 << " " << ny2 << " " << nz2 << std::endl;
    for (auto v : vec2)
        std::cout << v << " ";
    std::cout << std::endl;
    return 0;
}