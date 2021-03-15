//
// Created by Minghao Guo on 2021/3/4.
//

#ifndef INCLUDE_PITECHCYLINDER_H
#define INCLUDE_PITECHCYLINDER_H
#pragma once

class PitechCylinder
{
private:
    float inner_radius = 389.72f;
    float outer_radius = 409.72f;

    int nPanel = 20;

    int nPicoPerPanelZ = 2;
    int nPicoPerPanelY = 2;
    float mvPicoZ = 80.f;
    float mvPicoY = 60.f;

    int nSubPerPicoZ = 4;
    int nSubPerPicoY = 3;
    float mvSubZ = 20.f;
    float mvSubY = 20.f;

    int nCryPerSubZ = 6;
    int nCryPerSubY = 6;
    float mvCryZ = 3.2f;
    float mvCryY = 3.2f;
    float szCryZ = 3.f;
    float szCryY = 3.f;

public:
    int nCrystal() {return this->n}


};
#endif //INCLUDE_PITECHCYLINDER_H
