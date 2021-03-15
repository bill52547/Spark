//
// Created by Minghao Guo on 2021/2/25.
//

#include "image.h"
#include "../../src/include/rawdata_io.h"
#include "../../src/include/arithmetic.h"
#include <nlohmann/json.hpp>
#include <iomanip>

using json = nlohmann::json;

void Image::write(std::string & path) const
{
    std::ofstream FILE(path, std::ios::out | std::ofstream::binary);
    scalar_writer(FILE, this->shape.x);
    scalar_writer(FILE, this->shape.y);
    scalar_writer(FILE, this->shape.z);
    vector_writer(FILE, this->affine.data);

    FILE.seekp(data_byte_shift, std::ios::beg);
    vector_writer(FILE, this->data);
    FILE.close();
}

void Image::write_json(const std::string & path) const
{
    size_t lastindex = path.find_last_of(".");
    std::string raw_path = path.substr(0, lastindex);
    std::string data_path = raw_path + "_data.bin";
    json j;
    j["shape_x"] = this->shape.x;
    j["shape_y"] = this->shape.y;
    j["shape_z"] = this->shape.z;
    j["affine"] = std::vector<float>(this->affine.data.begin(), this->affine.data.end());
    j["data_path"] = data_path;
    std::ofstream FILE(data_path, std::ios::out | std::ofstream::binary);
    vector_writer(FILE, this->data);
    std::ofstream o(path);
    o << std::setw(4) << j << std::endl;
}

Image Image::read(std::string & path)
{
    Shape shape;
    std::ifstream FILE(path, std::ios::in | std::ifstream::binary);
    shape.x = scalar_reader<int>(FILE);
    shape.y = scalar_reader<int>(FILE);
    shape.z = scalar_reader<int>(FILE);
    Affine affine = Affine(vector_reader<float>(FILE, 16));

    FILE.seekg(data_byte_shift, std::ios::beg);

    vec_float data = vector_reader<float>(FILE, shape.x * shape.y * shape.z);
    return Image(shape, affine, data);
}

Image Image::read_json(const std::string & path)
{
    std::ifstream i(path);
    json j;
    i >> j;

    Shape shape = {j["shape_x"], j["shape_y"], j["shape_z"]};
    Affine affine = Affine(j["affine"]);
    std::string data_path = j["data_path"];
    std::ifstream FILE(data_path, std::ios::in | std::ifstream::binary);
    vec_float data = vector_reader<float>(FILE, shape.x * shape.y * shape.z);
    return Image(shape, affine, data);
}

Image Image::operator+ (const float v)
{
    return this->UpdateData(this->data + v);
}

Image Image::operator+ (const Image & image2)
{
    return this->UpdateData(this->data + image2.GetData());
}

Image operator+ (const float v, Image & other)
{
    return other.UpdateData(v + other.GetData());
}

Image Image::operator- (const float v)
{
    return this->UpdateData(this->data - v);
}

Image Image::operator- (const Image & image2)
{
    return this->UpdateData(this->data - image2.GetData());
}

Image operator- (const float v, Image & other)
{
    return other.UpdateData(v - other.GetData());
}

Image Image::operator* (const float v)
{
    return this->UpdateData(this->data * v);
}

Image Image::operator* (const Image & image2)
{
    return this->UpdateData(this->data * image2.GetData());
}

Image operator* (const float v, Image & other)
{
    return other.UpdateData(v * other.GetData());
}

Image Image::operator/ (const float v)
{
    return this->UpdateData(this->data / v);
}

Image Image::operator/ (const Image & image2)
{
    return this->UpdateData(this->data / image2.GetData());
}

Image operator/ (const float v, Image & other)
{
    return other.UpdateData(v / other.GetData());
}


