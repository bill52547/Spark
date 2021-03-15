//
// Created by Minghao Guo on 2021/3/10.
//

#ifndef INCLUDE_OSEM_H
#define INCLUDE_OSEM_H
#include "Projector.h"
#include "BackProjector.h"
#include <thrust/device_vector.h>
#include "../config/config.h"

class OSEM {
private:
    float CTR = DEFAULT_CTR;
    Projector projector;
    BackProjector bprojector;
public:
    OSEM(Projector & projector_, BackProjector & bprojector_):
    projector(projector_), bprojector(bprojector_) {}

    Image operator() (const int n_iter = 5, const int n_sub = 5)
    {
        Image image =
        for (int iter = 0; iter < n_iter; iter ++)
        {

        }
    }
};


#endif //INCLUDE_OSEM_H
