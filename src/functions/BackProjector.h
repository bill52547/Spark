//
// Created by Minghao Guo on 2021/3/5.
//

#ifndef INCLUDE_BACKPROJECTOR_H
#define INCLUDE_BACKPROJECTOR_H
#pragma once
#include <thrust/device_vector.h>
#include "../datatype/LineOfResponse.h"
#include "../datatype/listmode.h"
#include "../datatype/image.h"
//#include "../include/geometric.h"
//#include "../geometry/PitechCylinder.h"

using namespace thrust;
//PitechCylinder scanner_20panel;

class BackProjector {
public:
    BackProjector(const float ctr_, const Image image_):
    CTR(ctr_), image_template(image_) {}

    Image operator() (Listmode & listmode);

private:
    float CTR;
    Image image_template;

};

#endif //INCLUDE_BACKPROJECTOR_H
