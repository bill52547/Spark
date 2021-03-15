//
// Created by Minghao Guo on 2021/3/10.
//

#ifndef INCLUDE_GEOMETRIC_H
#define INCLUDE_GEOMETRIC_H
#pragma once

#include <math.h>

__device__ __host__
float cal_dist(const float x1, const float y1, const float z1,
               const float x2, const float y2, const float z2) {
    return std::sqrt((x1 - x2) * (x1 - x2) +
                 (y1 - y2) * (y1 - y2) +
                 (z1 - z2) * (z1 - z2));
}

#endif //INCLUDE_GEOMETRIC_H
