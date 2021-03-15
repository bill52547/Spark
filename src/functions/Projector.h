//
// Created by Minghao Guo on 2021/3/5.
//

#ifndef INCLUDE_PROJECTOR_H
#define INCLUDE_PROJECTOR_H
#pragma once

#include <thrust/device_vector.h>
#include "../datatype/LineOfResponse.h"
#include "../datatype/listmode.h"
#include "../datatype/image.h"
#include "../geometry/PitechCylinder.h"

using namespace thrust;

class Projector {
private:
    float CTR;
    LineOfResponse lor;

public:
    Projector(const float ctr_, const LineOfResponse & lor_):
    CTR(ctr_), lor(lor_) {}

    Listmode operator() (Image & image);
};


#endif //INCLUDE_PROJECTOR_H
