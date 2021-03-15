//
// Created by Minghao Guo on 2021/3/4.
//

#ifndef INCLUDE_LINEOFRESPONSE_H
#define INCLUDE_LINEOFRESPONSE_H
#include <cmath>
#include "../config/config.h"
#include <thrust/device_vector.h>

#define IndexType LOR_INDEX_TYPE
using namespace thrust;

class LineOfResponse {
public:
    int num;
#if LOR_WITH_INDEX
    device_vector<IndexType> index1 = device_vector<IndexType>(0);
    device_vector<IndexType> index2 = device_vector<IndexType>(0);
    device_vector<float> lut_pos = device_vector<float>(0);
    float min_gap = LOR_MIN_GAP;
    float max_z_gap = LOR_MAX_Z_GAP;
#else
    device_vector<float> pos1 = device_vector<float>(0);
    device_vector<float> pos2 = device_vector<float>(0);
#endif // LOR_WITH_INDEX

#if LOR_WITH_TIME_DIFF
    device_vector<float> time_diff = device_vector<float>(0); // arrive time index2 - index1
    float time_win = LOR_TIME_WIN;
#endif // LOR_WITH_TIME_DIFF

#if LOR_WITH_TABLE_Z
    device_vector<float> table_z = device_vector<float>(0);
#endif // LOR_WITH_TABLE_Z

#if LOR_WITH_ENERGY
    device_vector<unsigned short> energy1 = device_vector<unsigned short>(0);
    device_vector<unsigned short> energy2 = device_vector<unsigned short>(0);
    unsigned short en_low = ENERGY_LOW;
    unsigned short en_high = ENERGY_HIGH;
#endif // LOR_WITH_ENERGY

public:
    LineOfResponse(const int num_): num(num_)
    {}

#if LOR_WITH_INDEX
    LineOfResponse(const device_vector<IndexType> & index1_,
             const device_vector<IndexType> & index2_):
             index1(index1_), index2(index2_)
    {
        this->num = index1_.size();
    }

    __host__
    void SetLutPos(const device_vector<float> & lut_pos_)
    {
        this->lut_pos = lut_pos_;
    }

    __host__
    device_vector<float>& GetLutPos()
    {
        return this->lut_pos;
    }

    __host__
    float* GetLutPosRawPtr()
    {
        return thrust::raw_pointer_cast(this->lut_pos.data());
    }

    __host__ __device__
    int GetNum() const
    {
        return this->num;
    }

    __host__
    device_vector<IndexType>& GetIndex1()
    {
        return this->index1;
    }

    __host__
    IndexType * GetIndex1RawPtr()
    {
        return thrust::raw_pointer_cast(this->index1.data());
    }

    __host__ __device__
    IndexType GetIndex1(const int ind)
    {
        return this->index1[ind];
    }

    __host__
    device_vector<IndexType>& GetIndex2()
    {
        return this->index2;
    }

    __host__
    IndexType * GetIndex2RawPtr()
    {
        return thrust::raw_pointer_cast(this->index2.data());
    }

    __host__ __device__
    IndexType GetIndex2(const int ind)
    {
        return this->index2[ind];
    }

    __host__
    device_vector<float> GetX1();

    __host__
    device_vector<float> GetX2();

    __host__
    device_vector<float> GetY1();

    __host__
    device_vector<float> GetY2();

    __host__
    device_vector<float> GetZ1();

    __host__
    device_vector<float> GetZ2();
//    __device__ __host__
//    float GetX1(const int ind)
//    {
//        return this->lut_pos[this->index1[ind] + MAX_CRYSTAL_ID * 0];
//    }
//
//    __device__ __host__
//    float GetX2(const int ind)
//    {
//        return this->lut_pos[this->index2[ind] + MAX_CRYSTAL_ID * 0];
//    }
//
//    __device__ __host__
//    float GetY1(const int ind)
//    {
//        return this->lut_pos[this->index1[ind] + MAX_CRYSTAL_ID * 1];
//    }
//
//    __device__ __host__
//    float GetY2(const int ind)
//    {
//        return this->lut_pos[this->index2[ind] + MAX_CRYSTAL_ID * 1];
//    }

#if LOR_WITH_TABLE_Z


//    __device__ __host__
//    float GetZ1(const int ind)
//    {
//        return this->lut_pos[this->index1[ind] + MAX_CRYSTAL_ID * 2] + this->GetTableZ(ind);
//    }
//
//    __device__ __host__
//    float GetZ2(const int ind)
//    {
//        return this->lut_pos[this->index2[ind] + MAX_CRYSTAL_ID * 2] + this->GetTableZ(ind);
//    }

#else // not LOR_WITH_TABLE_Z
//    __device__
//    float GetZ1(const int ind)
//    {
//        return this->lut_pos[this->index1[ind] + MAX_CRYSTAL_ID * 2];
//    }
//
//    __device__
//    float GetZ2(const int ind)
//    {
//        return this->lut_pos[this->index2[ind] + MAX_CRYSTAL_ID * 2];
//    }

#endif // LOR_WITH_TABLE_Z

//    __device__ __host__
//    float GetLorLength(const int ind)
//    {
//        float pos1x = this->GetX1(ind),
//              pos1y = this->GetY1(ind),
//              pos1z = this->GetZ1(ind);
//        float pos2x = this->GetX2(ind),
//              pos2y = this->GetY2(ind),
//              pos2z = this->GetZ2(ind);
//        return std::sqrt((pos1x - pos2x) * (pos1x - pos2x) +
//                         (pos1y - pos2y) * (pos1y - pos2y) +
//                         (pos1z - pos2z) * (pos1z - pos2z));
//    }

//    __device__ __host__
//    bool IsGapGood(const int ind)
//    {
//        float pos1z = this->GetZ1(ind);
//        float pos2z = this->GetZ2(ind);
//        if (std::abs(pos1z - pos2z) > this->max_z_gap) {return false;}
//        if (this->GetLorLength(ind) < this->min_gap) {return false;}
//        return true;
//    }

    __host__
    device_vector<bool> IsGapGood();

#if LOR_WITH_TIME_DIFF
    LineOfResponse(const device_vector<IndexType> & index1_,
             const device_vector<IndexType> & index2_,
             const device_vector<float> & time_diff_):
             index1(index1_), index2(index2_), time_diff(time_diff_)
    {
        this->num = index1_.size();
    }

    __host__
    device_vector<float>& GetTimeDiff()
    {
        return this->time_diff;
    }

    __host__
    float* GetTimeDiffRawPtr()
    {
        return thrust::raw_pointer_cast(this->time_diff.data());
    }

    __host__ __device__
    float GetTimeDiff(const int ind)
    {
        if (this->time_diff.size() == 0) {return 0.f;}
        return this->time_diff[ind];
    }

//    __device__ __host__
//    bool InTimeWindow(const int ind)
//    {
//        if (this->time_win <= 0) {return true;}
//        if (std::abs(this->GetTimeDiff(ind)) > this->time_win)
//        {
//            return false;
//        }
//        return true;
//    }

    __host__
    device_vector<bool> InTimeWindow();
#else
    __host__
    device_vector<bool> InTimeWindow();
//    __device__
//    bool InTimeWindow(const int ind)
//    {
//        return true;
//    }
#endif // LOR_WITH_TIME_DIFF
#endif // LOR_WITH_INDEX

#if LOR_WITH_TABLE_Z
    __host__
    void SetTableZ(const device_vector<float> table_z_)
    {
        if (this->table_z.size() == 0)
        {
            this->table_z.resize(this->num);
        }
        this->table_z = table_z_;
    }

    __host__
    device_vector<float>* GetTableZ()
    {
        return &this->table_z;
    }

    __host__ __device__
    float GetTableZ(const int ind)
    {
        if (this->table_z.size() == 0)
        {return 0.f;}
        else
        {return this->table_z[ind];}
    }
#endif // LOR_WITH_TABLE_Z
#if LOR_WITH_ENERGY
    __host__
    void SetEnergy(const device_vector<unsigned short> energy1_,
                   const device_vector<unsigned short> energy2_)
    {
        if (this->energy1.size() == 0)
        {
            this->energy1.resize(this->num);
        }
        if (this->energy2.size() == 0)
        {
            this->energy2.resize(this->num);
        }
        this->energy1 = energy1_;
        this->energy2 = energy2_;
    }

    __host__
    device_vector<unsigned short>& GetEnergy1()
    {
        return this->energy1;
    }

    __host__
    device_vector<unsigned short>& GetEnergy2()
    {
        return this->energy2;
    }

    __host__ __device__
    float GetEnergy1(const int ind)
    {
        if (this->energy1.size() == 0)
        {return 511;}
        else
        {return this->energy1[ind];}
    }

    __host__ __device__
    float GetEnergy2(const int ind)
    {
        if (this->energy2.size() == 0)
        {return 511;}
        else
        {return this->energy2[ind];}
    }

//    __device__ __host__
//    bool InEnergyWindow(const int ind)
//    {
//        if (this->GetEnergy1(ind) > this->en_high) {return false;}
//        if (this->GetEnergy1(ind) < this->en_low) {return false;}
//        if (this->GetEnergy2(ind) > this->en_high) {return false;}
//        if (this->GetEnergy2(ind) < this->en_low) {return false;}
//        return true;
//    }

    __host__
    device_vector<bool> InEnergyWindow();

#else
    __host__
    device_vector<bool> InEnergyWindow();
//    __device__
//    bool InEnergyWindow(const int ind)
//    {
//        return true;
//    }
#endif // LOR_WITH_ENERGY

//    __device__ __host__
//    bool IsAllGood(const int ind)
//    {
//        if (!this->IsGapGood(ind)) {return false;}
//        if (!this->InTimeWindow(ind)) {return false;}
//        if (!this->InEnergyWindow(ind)) {return false;}
//        return true;
//    }

    __host__
    device_vector<bool> IsAllGood();

    __host__
    LineOfResponse FilterAllGood();

    void write_json(const std::string & filename) const;
    static LineOfResponse read_json(const std::string & filename);

#if LOR_WITH_POS
    Listmode(const device_vector<float> & pos1_,
             const device_vector<float> & pos2_):
             pos1(pos1_), pos2(pos2_)
    {
        this->num = pos1_.size() / 3;
    }

#if LOR_WITH_TIME_DIFF
    Listmode(const device_vector<float> & pos1_,
             const device_vector<float> & pos1_,
             const device_vector<float> & time_diff_:
             pos1(pos1_), pos2(pos2_), time_diff(time_diff_)
    {
        this->num = pos1_.size() / 3;
    }
#endif // LOR_WITH_TIME_DIFF
#endif // LOR_WITH_POS

};


#endif //INCLUDE_LINEOFRESPONSE_H
