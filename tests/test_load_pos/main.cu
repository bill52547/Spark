//
// Created by Minghao Guo on 2021/2/25.
//

#include <thrust/device_vector.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unistd.h>
#include <iomanip>
#include "../../src/geometry/Lut.h"
#include "../../src/config/config.h"

int main()
{
    std::string filename = "pos_raw.bin";
    PosLutBoundary pos = PosLutBoundary::read_raw(filename);
    for (auto i = 0; i < 10; i++)
    {
        std::cout << i << ": " << pos.data[i] << ","
        << pos.data[i + MAX_CRYSTAL_ID * 1] << ","
        << pos.data[i + MAX_CRYSTAL_ID * 2] << ","
        << pos.data[i + MAX_CRYSTAL_ID * 3] << ","
        << pos.data[i + MAX_CRYSTAL_ID * 4] << ","
        << pos.data[i + MAX_CRYSTAL_ID * 5] << "\n";
    }
    return 0;
}