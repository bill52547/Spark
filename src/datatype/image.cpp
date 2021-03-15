//
// Created by Minghao Guo on 2021/3/15.
//

#include "image.h"

#include "../config/config.h"
#include <highfive/H5File.hpp>
#include <highfive/H5DataSet.hpp>
#include <highfive/H5DataSpace.hpp>
#include <highfive/H5DataType.hpp>

using namespace HighFive;

void Image::H5Dump(const std::string & filename) const
{
    File file(filename, File::ReadWrite | File::Create | File::Truncate);
    // Create the dataset
    DataSet dataset_shape_x = file.createDataSet<int>(
            std::string("shape_x"), DataSpace::From(this->shape.x));
    dataset_shape_x.write(this->shape.x);
    DataSet dataset_shape_y = file.createDataSet<int>(
            std::string("shape_y"), DataSpace::From(this->shape.y));
    dataset_shape_y.write(this->shape.y);
    DataSet dataset_shape_z = file.createDataSet<int>(
            std::string("shape_z"), DataSpace::From(this->shape.z));
    dataset_shape_z.write(this->shape.z);

    std::vector<float> host_vec_affine(this->affine.data.begin(), this->affine.data.end());
    DataSet dataset_affine = file.createDataSet<float>(std::string("affine"), DataSpace::From(host_vec_affine));
    dataset_affine.write(host_vec_affine);

    std::vector<float> host_vec_data(this->data.begin(), this->data.end());
    DataSet dataset_data = file.createDataSet<float>(std::string("data"), DataSpace::From(host_vec_data));
    dataset_data.write(host_vec_data);
}
