//
// Created by Minghao Guo on 2021/3/4.
//

#include "LineOfResponse.h"
#include <thrust/transform.h>
#include <thrust/functional.h>
#include <thrust/gather.h>

using namespace thrust;
using namespace thrust::placeholders;


__host__
device_vector<float> LineOfResponse::GetX1()
{
    device_vector<float> pos_x1(this->num);
    thrust::gather(this->index1.begin(),
                 this->index1.end(),
                 this->lut_pos.begin(),
                 pos_x1.begin());
    return pos_x1;
}

__host__
device_vector<float> LineOfResponse::GetX2()
{
    device_vector<float> pos_x1(this->num);
    thrust::gather(this->index1.begin(),
                   this->index1.end(),
                   this->lut_pos.begin() + MAX_CRYSTAL_ID * 3,
                   pos_x1.begin());
    return pos_x1;
}

__host__
device_vector<float> LineOfResponse::GetY1()
{
    device_vector<float> pos_x1(this->num);
    thrust::gather(this->index1.begin(),
                   this->index1.end(),
                   this->lut_pos.begin() + MAX_CRYSTAL_ID * 1,
                   pos_x1.begin());
    return pos_x1;
}

__host__
device_vector<float> LineOfResponse::GetY2()
{
    device_vector<float> pos_x1(this->num);
    thrust::gather(this->index1.begin(),
                   this->index1.end(),
                   this->lut_pos.begin() + MAX_CRYSTAL_ID * 4,
                   pos_x1.begin());
    return pos_x1;
}

__host__
device_vector<float> LineOfResponse::GetZ1()
{
    device_vector<float> pos_x1(this->num);
    thrust::gather(this->index1.begin(),
                   this->index1.end(),
                   this->lut_pos.begin() + MAX_CRYSTAL_ID * 2,
                   pos_x1.begin());
    return pos_x1;
}

__host__
device_vector<float> LineOfResponse::GetZ2()
{
    device_vector<float> pos_x1(this->num);
    thrust::gather(this->index1.begin(),
                   this->index1.end(),
                   this->lut_pos.begin() + MAX_CRYSTAL_ID * 5,
                   pos_x1.begin());
    return pos_x1;
}

#include "../../src/include/functor.h"
#include "../../src/include/arithmetic.h"

__host__
device_vector<bool> LineOfResponse::IsGapGood()
{
    device_vector<float> xd = absolute<float>(this->GetX2() - this->GetX1());
    device_vector<float> yd = absolute<float>(this->GetY2() - this->GetY1());
    device_vector<float> zd = absolute<float>(this->GetZ2() - this->GetZ1());
    device_vector<float> dd = sqrt<float>(xd * xd + yd * yd + zd * zd);
    device_vector<bool> filt1(this->num);
    thrust::transform(zd.begin(), zd.end(), filt1.begin(), le_functor<float>(LOR_MAX_Z_GAP));
    device_vector<bool> filt2(this->num);
    thrust::transform(dd.begin(), dd.end(), filt2.begin(), ge_functor<float>(LOR_MIN_GAP));
    thrust::transform(filt1.begin(), filt1.end(), filt2.begin(), filt1.begin(), _1 && _2);
    return filt1;
}

#if LOR_WITH_TIME_DIFF
__host__
device_vector<bool> LineOfResponse::InTimeWindow()
{
    device_vector<bool> results(this->num);
    if (this->time_win <= 0 || this->time_diff.size() == 0) {
        thrust::fill(results.begin(), results.end(), true);
        return results;
    }

    device_vector<float> abs_time_diff = absolute<float>(this->time_diff);

    thrust::transform(abs_time_diff.begin(),
                      abs_time_diff.end(),
                      results.begin(),
                      le_functor<float>(this->time_win));
    return results;
}
#else // LOR_WITH_TIME_DIFF
__host__
device_vector<bool> LineOfResponse::InTimeWindow()
{
    device_vector<bool> results(this->num);
    thrust::fill(results.begin(), results.end(), true);
    return results;
}
#endif // LOR_WITH_TIME_DIFF

#if LOR_WITH_ENERGY
__host__
device_vector<bool> LineOfResponse::InEnergyWindow()
{
    device_vector<bool> filt1_low(this->num);
    device_vector<bool> filt1_high(this->num);
    device_vector<bool> filt2_low(this->num);
    device_vector<bool> filt2_high(this->num);
    device_vector<bool> results(this->num);

    if (this->energy1.size() == 0 || this->energy2.size() == 0) {
        thrust::fill(results.begin(), results.end(), true);
        return results;
    }

    thrust::transform(this->energy1.begin(),
                      this->energy1.end(),
                      filt1_low.begin(),
                      ge_functor<float>(this->en_low));

    thrust::transform(this->energy1.begin(),
                      this->energy1.end(),
                      filt1_high.begin(),
                      le_functor<float>(this->en_low));

    thrust::transform(this->energy2.begin(),
                      this->energy2.end(),
                      filt2_low.begin(),
                      ge_functor<float>(this->en_low));

    thrust::transform(this->energy2.begin(),
                      this->energy2.end(),
                      filt2_high.begin(),
                      le_functor<float>(this->en_low));

    thrust::transform(filt1_low.begin(), filt1_low.end(), filt1_high.begin(), filt1_low.begin(), _1 && _2);
    thrust::transform(filt2_low.begin(), filt2_low.end(), filt2_high.begin(), filt2_low.begin(), _1 && _2);
    thrust::transform(filt2_low.begin(), filt2_low.end(), filt2_low.begin(), filt1_low.begin(), _1 && _2);
    return filt1_low;
}
#else // LOR_WITH_ENERGY
__host__
device_vector<bool> LineOfResponse::InEnergyWindow()
{
    device_vector<bool> results(this->num);
    thrust::fill(results.begin(), results.end(), true);
    return results;
}
#endif // LOR_WITH_ENERGY

__host__
device_vector<bool> LineOfResponse::IsAllGood()
{
    device_vector<bool> filt1 = this->IsGapGood();
    device_vector<bool> filt2 = this->InTimeWindow();
    device_vector<bool> filt3 = this->InEnergyWindow();
    thrust::transform(filt1.begin(), filt1.end(), filt2.begin(), filt1.begin(), _1 && _2);
    thrust::transform(filt1.begin(), filt1.end(), filt3.begin(), filt1.begin(), _1 && _2);
    return filt1;
}

struct _is_true
{
    __device__
    bool operator() (const bool x)
    {
        return x;
    }
};

#include <thrust/copy.h>
#include "../include/reduce.h"

__host__
LineOfResponse LineOfResponse::FilterAllGood()
{
    device_vector<bool> stencil = this->IsAllGood();
    int count_all_good = count_true(stencil);
    device_vector<IndexType> new_index1(count_all_good);
    device_vector<IndexType> new_index2(count_all_good);
    device_vector<float> new_time_diff(0);
    device_vector<float> new_table_z(0);
    device_vector<unsigned short> new_energy1(0);
    device_vector<unsigned short> new_energy2(0);

#if LOR_WITH_TIME_DIFF
    if (this->time_diff.size() > 0) {new_time_diff.resize(count_all_good);}
#endif // LOR_WITH_TIME_DIFF

#if LOR_WITH_TABLE_Z
if (this->table_z.size() > 0) {new_table_z.resize(count_all_good);}
#endif // LOR_WITH_TABLE_Z

#if LOR_WITH_ENERGY
    if (this->energy1.size() > 0 && this->energy2.size() > 0)
    {
        new_energy1.resize(count_all_good);
        new_energy2.resize(count_all_good);
    }
#endif // LOR_WITH_ENERGY
#if LOR_WITH_TIME_DIFF
    LineOfResponse new_lor = {new_index1, new_index2, new_time_diff};
#else // LOR_WITH_TIME_DIFF
    LineOfResponse new_lor = {new_index1, new_index2};
#endif // LOR_WITH_TIME_DIFF
    new_lor.SetLutPos(this->lut_pos);
#if LOR_WITH_TABLE_Z
    new_lor.SetTableZ(new_table_z);
#endif // LOR_WITH_TABLE_Z
#if LOR_WITH_ENERGY
    new_lor.SetEnergy(new_energy1, new_energy2);
#endif // LOR_WITH_ENERGY
    return new_lor;
}

#include <nlohmann/json.hpp>
#include <iomanip>
#include <fstream>
#include "../../src/include/rawdata_io.h"

using json = nlohmann::json;

void LineOfResponse::write_json(const std::string & path) const {
    size_t lastindex = path.find_last_of(".");
    std::string raw_path = path.substr(0, lastindex);
    json j;
    j["LOR_WITH_INDEX"] = LOR_WITH_INDEX;
    j["LOR_WITH_TIME_DIFF"] = LOR_WITH_TIME_DIFF;
    j["LOR_WITH_TABLE_Z"] = LOR_WITH_TABLE_Z;
    j["LOR_WITH_ENERGY"] = LOR_WITH_ENERGY;
    j["num"] = this->num;

    std::string data_path = raw_path + "_data.bin";
    std::ofstream FILE(data_path, std::ios::out | std::ofstream::binary);
    j["data_path"] = data_path;


#if LOR_WITH_INDEX
    j["LOR_MIN_GAP"] = LOR_MIN_GAP;
    j["LOR_MAX_Z_GAP"] = LOR_MAX_Z_GAP;
    std::string lut_pos_path = raw_path + "_lut_pos.bin";
    // std::string index1_path = raw_path + "_index1.bin";
    // std::string index2_path = raw_path + "_index2.bin";
    // std::ofstream FILE1(index1_path, std::ios::out | std::ofstream::binary);
    vector_writer(FILE, this->index1);
    // j["index1_path"] = index1_path;

    // std::ofstream FILE2(index2_path, std::ios::out | std::ofstream::binary);
    vector_writer(FILE, this->index2);
    // j["index2_path"] = index2_path;

    std::ofstream FILE3(lut_pos_path, std::ios::out | std::ofstream::binary);
    vector_writer(FILE3, this->lut_pos);
    j["lut_pos_path"] = lut_pos_path;
#endif // LOR_WITH_INDEX

#if LOR_WITH_TIME_DIFF
    j["time_win"] = time_win;
    // std::string time_diff_path = raw_path + "_time_diff.bin";
    // std::ofstream FILE(time_diff_path, std::ios::out | std::ofstream::binary);
    vector_writer(FILE, this->time_diff);
    // j["time_diff_path"] = time_diff_path;
#endif // LOR_WITH_TIME_DIFF

#if LOR_WITH_TABLE_Z
    // std::string table_z_path = raw_path + "_table_z.bin";
    // std::ofstream FILE(table_z_path, std::ios::out | std::ofstream::binary);
    vector_writer(FILE, this->table_z);
    // j["table_z_path"] = table_z_path;
#endif // LOR_WITH_TABLE_Z

#if LOR_WITH_ENERGY
    j["en_low"] = ENERGY_LOW;
    j["en_high"] = ENERGY_HIGH;

    // std::string energy1_path = raw_path + "_energy1.bin";
    // std::ofstream FILE1(energy1_path, std::ios::out | std::ofstream::binary);
    vector_writer(FILE, this->energy1);
    // j["energy1_path"] = energy1_path;

    // std::string energy2_path = raw_path + "_energy2.bin";
    // std::ofstream FILE2(energy2_path, std::ios::out | std::ofstream::binary);
    vector_writer(FILE, this->energy2);
    // j["energy2_path"] = energy2_path;
#endif // LOR_WITH_ENERGY

    std::ofstream o(path);
    o << std::setw(4) << j << std::endl;
}

LineOfResponse LineOfResponse::read_json(const std::string & filename)
{
    std::ifstream i(filename);
    json j;
    i >> j;
    assert(j["LOR_WITH_INDEX"] == LOR_WITH_INDEX);

    int num = j["num"];
    LineOfResponse lor(num);
    std::string data_path = j["data_path"];
    std::ifstream FILE(data_path, std::ios::in | std::ifstream::binary);

#if LOR_WITH_INDEX
    // std::string index1_path = j["index1_path"];
    // std::ifstream FILE1(index1_path, std::ios::in | std::ifstream::binary);
    device_vector<IndexType> index1 = vector_reader<IndexType>(FILE, num);

    // std::string index2_path = j["index2_path"];
    // std::ifstream FILE2(index2_path, std::ios::in | std::ifstream::binary);
    device_vector<IndexType> index2 = vector_reader<IndexType>(FILE, num);

    std::string lut_pos_path = j["lut_pos_path"];
    std::ifstream FILE3(lut_pos_path, std::ios::in | std::ifstream::binary);
    device_vector<float> lut_pos = vector_reader<float>(FILE3, num * 6);
#endif // LOR_WITH_INDEX

    assert(j["LOR_WITH_TIME_DIFF"] == LOR_WITH_TIME_DIFF);
#if LOR_WITH_TIME_DIFF
    // std::string time_diff_path = j["time_diff_path"];
    // std::ifstream FILE(time_diff_path, std::ios::in | std::ifstream::binary);
    device_vector<float> time_diff = vector_reader<float>(FILE, num);
    lor = LineOfResponse(index1, index2, time_diff);
#else
    lor = LineOfResponse(index1, index2);
#endif // LOR_WITH_TIME_DIFF
    lor.SetLutPos(lut_pos);

    assert(j["LOR_WITH_TABLE_Z"] == LOR_WITH_TABLE_Z);

#if LOR_WITH_TABLE_Z
    // std::string table_z_path = j["table_z_path"];
    // std::ifstream FILE(table_z_path, std::ios::in | std::ifstream::binary);
    device_vector<float> table_z = vector_reader<float>(FILE, num);
    lor.SetTableZ(table_z);
#endif // LOR_WITH_TABLE_Z

    assert(j["LOR_WITH_ENERGY"] == LOR_WITH_ENERGY);
#if LOR_WITH_ENERGY
    // std::string energy1_path = j["energy1_path"];
    // std::ifstream FILE1(energy1_path, std::ios::in | std::ifstream::binary);
    device_vector<unsigned short> energy1 = vector_reader<unsigned short>(FILE, num);

    // std::string energy2_path = j["energy2_path"];
    // std::ifstream FILE2(energy2_path, std::ios::in | std::ifstream::binary);
    device_vector<unsigned short> energy2 = vector_reader<unsigned short>(FILE, num);
    lor.SetEnergy(energy1, energy2);
#endif // LOR_WITH_ENERGY

    return lor;
}
