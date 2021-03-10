//
// Created by Minghao Guo on 2021/3/4.
//

#ifndef INCLUDE_PITECHCYLINDER_H
#define INCLUDE_PITECHCYLINDER_H
#pragma once

#include <math.h>
#include <cmath>
#include "../config/config.h"
#include "../include/arithmetic.h"
#define IndexType LOR_INDEX_TYPE

class PitechCylinder
{
public:
    float inner_radius = 389.72f;
    float outer_radius = 409.72f;

    IndexType nPanel = 20;

    IndexType nPicoPerPanelZ = 2;
    IndexType nPicoPerPanelY = 2;
    float mvPicoZ = 80.4f;
    float mvPicoY = 60.4f;

    IndexType nSubPerPicoZ = 4;
    IndexType nSubPerPicoY = 3;
    float mvSubZ = 20.f;
    float mvSubY = 20.f;

    IndexType nCryPerSubZ = 6;
    IndexType nCryPerSubY = 6;
    float mvCryZ = 3.2f;
    float mvCryY = 3.2f;
    float szCryZ = 3.f;
    float szCryY = 3.f;

public:
    float avgRadius() const {return (this->inner_radius + this->outer_radius) / 2.f;}
    float PanelAngle() const {return M_PI * 2 / this->nPanel;}
    float gapCryZ() const {return this->mvCryZ - this->szCryZ;}
    float gapCryY() const {return this->mvCryY - this->szCryY;}

    float szSubZ() const {return this->mvCryZ * this->nCryPerSubZ - this->gapCryZ();}
    float szSubY() const {return this->mvCryY * this->nCryPerSubY - this->gapCryY();}
    float gapSubZ() const {return this->mvSubZ - this->szSubZ();}
    float gapSubY() const {return this->mvSubY - this->szSubY();}

    float szPicoZ() const {return this->mvSubZ * this->nSubPerPicoZ - this->gapSubZ();}
    float szPicoY() const {return this->mvSubY * this->nSubPerPicoY - this->gapSubY();}
    float gapPicoZ() const {return this->mvPicoZ - this->szPicoZ();}
    float gapPicoY() const {return this->mvPicoY - this->szPicoY();}

    float szPanelZ() const {return this->mvPicoZ * this->nPicoPerPanelZ - this->gapPicoZ();}
    float szPanelY() const {return this->mvPicoY * this->nPicoPerPanelY - this->gapPicoY();}

    float AxialLength() const {return this->szPanelZ();}

    IndexType nRing() const {return this->nCryPerPanelZ();}
    IndexType nSector() const {return this->nCryPerPanelY() * this->nPanel;}

    IndexType nCryPerSub() const {return this->nCryPerSubY * this->nCryPerSubZ; }
    IndexType nSubPerPico() const {return this->nSubPerPicoZ * this->nSubPerPicoY; }
    IndexType nPicoPerPanel() const {return this->nPicoPerPanelY * this->nPicoPerPanelZ; }

    IndexType nSubPerPanelZ() const {return this->nPicoPerPanelZ * this->nSubPerPicoZ;}
    IndexType nSubPerPanelY() const {return this->nPicoPerPanelY * this->nSubPerPicoY;}
    IndexType nSubPerPanel() const {return this->nSubPerPanelZ() * this->nSubPerPanelY();}

    IndexType nCryPerPicoZ() const {return this->nSubPerPicoZ * this->nCryPerSubZ;}
    IndexType nCryPerPicoY() const {return this->nSubPerPicoY * this->nCryPerSubY;}
    IndexType nCryPerPico() const {return this->nCryPerPicoZ() * this->nCryPerPicoY();}

    IndexType nCryPerPanelZ() const {return this->nPicoPerPanelZ * this->nCryPerPicoZ();}
    IndexType nCryPerPanelY() const {return this->nPicoPerPanelY * this->nCryPerPicoY();}
    IndexType nCryPerPanel() const {return this->nCryPerPanelZ() * this->nCryPerPanelY();}
    IndexType nCryAll() const {return this->nCryPerPanel() * this->nPanel;}

    IndexType GetCryIndex(const IndexType ind) {return ind % this->nCryPerSub(); }
    IndexType GetCryIndexY(const IndexType ind) {return this->GetCryIndex(ind) % this->nCryPerSubY;}
    IndexType GetCryIndexZ(const IndexType ind) {return this->GetCryIndex(ind) / this->nCryPerSubY;}
    device_vector<IndexType> GetCryIndex(const device_vector<IndexType> & ind) {return ind % this->nCryPerSub(); }
    device_vector<IndexType> GetCryIndexY(const device_vector<IndexType> & ind) {return this->GetCryIndex(ind) % this->nCryPerSubY; }
    device_vector<IndexType> GetCryIndexZ(const device_vector<IndexType> & ind) {return this->GetCryIndex(ind) / this->nCryPerSubY; }

    IndexType GetSubIndex(const IndexType ind) {return (ind / this->nCryPerSub()) % this->nSubPerPico(); }
    IndexType GetSubIndexY(const IndexType ind) {return this->GetSubIndex(ind) % this->nSubPerPicoY;}
    IndexType GetSubIndexZ(const IndexType ind) {return this->GetSubIndex(ind) / this->nSubPerPicoY;}
    device_vector<IndexType> GetSubIndex(const device_vector<IndexType> & ind) {return (ind / this->nCryPerSub()) % this->nSubPerPico(); }
    device_vector<IndexType> GetSubIndexY(const device_vector<IndexType> & ind) {return this->GetSubIndex(ind) % this->nSubPerPicoY; }
    device_vector<IndexType> GetSubIndexZ(const device_vector<IndexType> & ind) {return this->GetSubIndex(ind) / this->nSubPerPicoY; }

    IndexType GetPicoIndex(const IndexType ind) {return (ind / this->nCryPerSub() / this->nSubPerPico()) % this->nPicoPerPanel(); }
    IndexType GetPicoIndexY(const IndexType ind) {return this->GetPicoIndex(ind) % this->nPicoPerPanelY;}
    IndexType GetPicoIndexZ(const IndexType ind) {return this->GetPicoIndex(ind) / this->nPicoPerPanelY;}
    device_vector<IndexType> GetPicoIndex(const device_vector<IndexType> & ind) {return (ind / this->nCryPerSub() / this->nSubPerPico()) % this->nPicoPerPanel(); }
    device_vector<IndexType> GetPicoIndexY(const device_vector<IndexType> & ind) {return this->GetPicoIndex(ind) % this->nPicoPerPanelY;}
    device_vector<IndexType> GetPicoIndexZ(const device_vector<IndexType> & ind) {return this->GetPicoIndex(ind) / this->nPicoPerPanelY;}

    IndexType GetPanelIndex(const IndexType ind) {return ind / this->nCryPerPanel(); }
    device_vector<IndexType> GetPanelIndex(const device_vector<IndexType> & ind) {return ind / this->nCryPerPanel(); }

    IndexType GetRingIndex(const IndexType ind) {
        return this->GetPicoIndexZ(ind) * this->nCryPerPicoZ() +
        this->GetSubIndexZ(ind) * this->nCryPerSubZ +
        this->GetCryIndexZ(ind);
    }
    device_vector<IndexType> GetRingIndex(const device_vector<IndexType> & ind) {
        return this->GetPicoIndexZ(ind) * this->nCryPerPicoZ() +
               this->GetSubIndexZ(ind) * this->nCryPerSubZ +
               this->GetCryIndexZ(ind);
    }

    IndexType GetSectorIndex(const IndexType ind) {
        return this->GetPanelIndex(ind) * this->nCryPerPanel() +
               this->GetPicoIndexY(ind) * this->nCryPerPicoY() +
               this->GetSubIndexY(ind) * this->nCryPerSubY +
               this->GetCryIndexY(ind);
    }
    device_vector<IndexType> GetSectorIndex(const device_vector<IndexType> & ind) {
        return this->GetPanelIndex(ind) * this->nCryPerPanel() +
               this->GetPicoIndexY(ind) * this->nCryPerPicoY() +
               this->GetSubIndexY(ind) * this->nCryPerSubY +
               this->GetCryIndexY(ind);
    }

    float GetRingPosZ(const IndexType ring_ind)
    {
        IndexType ring_cry_ind = ring_ind % this->nCryPerSubZ;
        IndexType ring_sub_ind = (ring_ind / this->nCryPerSubZ) % this->nSubPerPicoZ;
        IndexType ring_pico_ind = (ring_ind / this->nCryPerSubZ / this->nSubPerPicoZ) % this->nPicoPerPanelZ;
        float sub_start = (this->szSubZ() - (this->mvCryZ * this->nCryPerSubZ - this->gapCryZ())) / 2.f;
        float pico_start = (this->szPicoZ() - (this->mvSubZ * this->nSubPerPicoZ - this->gapSubZ())) / 2.f;
        return static_cast<float>(ring_pico_ind * this->mvPicoZ + ring_sub_ind * this->mvSubZ + ring_cry_ind * this->mvCryZ) +
        this->szCryZ * 0.5f + sub_start + pico_start - this->AxialLength() / 2.f;
    }

    float GetSectorPosX(const IndexType sec_ind)
    {
        float start_angle = 0.f; // -.25f * M_PI
        IndexType sec_cry_ind = sec_ind % this->nCryPerSubY;
        IndexType sec_sub_ind = sec_ind / this->nCryPerSubY % this->nSubPerPicoY;
        IndexType sec_pico_ind = sec_ind / this->nCryPerSubY / this->nSubPerPicoY % this->nPicoPerPanelY;
        IndexType panel_ind = sec_ind / this->nCryPerSubY / this->nSubPerPicoY / this->nPicoPerPanelY;
        float sub_start = (this->szSubY() - (this->mvCryY * this->nCryPerSubY - this->gapCryY())) / 2.f;
        float pico_start = (this->szPicoY() - (this->mvSubY * this->nSubPerPicoY - this->gapSubY())) / 2.f;
        float panel_start = (this->szPanelY() - (this->mvPicoY * this->nPicoPerPanelY - this->gapPicoY())) / 2.f;
        float x_pos = static_cast<float>(sec_pico_ind * this->mvPicoY + sec_sub_ind * this->mvSubY + sec_cry_ind * this->mvCryY) +
                      this->szCryY * 0.5f + sub_start + pico_start + panel_start - this->szPanelY() / 2.f;
        float y_pos = this->avgRadius();

        float cos_angle = std::cos(panel_ind * this->PanelAngle() + start_angle);
        float sin_angle = std::sin(panel_ind * this->PanelAngle() + start_angle);
        return x_pos * cos_angle - y_pos * sin_angle;
    }

    float GetSectorPosY(const IndexType sec_ind)
    {
        float start_angle = 0.f; // -.25f * M_PI
        IndexType sec_cry_ind = sec_ind % this->nCryPerSubY;
        IndexType sec_sub_ind = sec_ind / this->nCryPerSubY % this->nSubPerPicoY;
        IndexType sec_pico_ind = sec_ind / this->nCryPerSubY / this->nSubPerPicoY % this->nPicoPerPanelY;
        IndexType panel_ind = sec_ind / this->nCryPerSubY / this->nSubPerPicoY / this->nPicoPerPanelY;
        float sub_start = (this->szSubY() - (this->mvCryY * this->nCryPerSubY - this->gapCryY())) / 2.f;
        float pico_start = (this->szPicoY() - (this->mvSubY * this->nSubPerPicoY - this->gapSubY())) / 2.f;
        float panel_start = (this->szPanelY() - (this->mvPicoY * this->nPicoPerPanelY - this->gapPicoY())) / 2.f;
        float x_pos = static_cast<float>(sec_pico_ind * this->mvPicoY + sec_sub_ind * this->mvSubY + sec_cry_ind * this->mvCryY) +
                      this->szCryY * 0.5f + sub_start + pico_start + panel_start - this->szPanelY() / 2.f;
        float y_pos = this->avgRadius();

        float cos_angle = std::cos(panel_ind * this->PanelAngle() + start_angle);
        float sin_angle = std::sin(panel_ind * this->PanelAngle() + start_angle);
        return x_pos * sin_angle + y_pos * cos_angle;
    }
};


#endif // INCLUDE_PITECHCYLINDER_H