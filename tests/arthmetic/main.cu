//
// Created by Minghao Guo on 2021/2/25.
//

#include <thrust/device_vector.h>
#include "datatype/image.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "helpers/timer.h"
#include <unistd.h>
#include <iomanip>
#include "helpers/tqdm.h"
#include "helpers/random_generator.h"
#include "include/arithmetic.h"
#include "include/comparison.h"

int main()
{
    const int num_disp = 2;
    Shape shape = Shape(32, 32, 32);
    const int num = shape.x * shape.y * shape.z;
    vec_float rand_ = normal_random<float>(num, 0, 1);
    Image image = Image(shape, Affine(), rand_);
    vec_float rand2_ = normal_random<float>(num, 0, 1);
    vec_float rand3_ = rand_ + rand2_;
    Image image2 = image + 1;
    thrust::device_vector<float> image_data = image.GetData(), image2_data = image2.GetData();
    for (int i = 0; i < 2; i++)
    {
        std::cout << "rand_[" << i << "] = " << rand_[i] << ", rand2_[" << i << "] = " << rand2_[i] << std::endl;
    }

    std::cout << "comparison: \n";
    for (int i = 0; i < num_disp; i++)
    {
        if ((rand_ > rand2_)[i] == 1.f)
        {
            std::cout << rand_[i] << " > " << rand2_[i] << std::endl;
        }
        else {
            std::cout << rand_[i] << " < " << rand2_[i] << std::endl;
        }
    }

    for (int i = 0; i < num_disp; i++)
    {
        if ((rand_ > rand2_)[i] == 1.f)
        {
            std::cout << rand_[i] << " > " << rand2_[i] << std::endl;
        }
        else {
            std::cout << rand_[i] << " < " << rand2_[i] << std::endl;
        }
    }

    std::cout << "absolute value: \n";
    auto rand1_abs = absolute(rand_);
    for (int i = 0; i < num_disp; i++)
    {
        std::cout << rand1_abs[i] << " ";
    }


    for (int i = 0; i < num_disp; i++)
    {
        std::cout << "image.data[" << i << "] + 1 = " << image_data[i] + 1 << ", image2.data[" << i << "] = " << image2_data[i] << std::endl;
    }
    Image image3 = image + image2;
    thrust::device_vector<float> image3_data = image3.GetData();
    for (int i = 0; i < num_disp; i++)
    {
        std::cout << "image.data[" << i << "] + image2.data[" << i << "] = " << image_data[i] + image2_data[i] << ", image3.data[" << i << "] = " << image3_data[i] << std::endl;
    }
    Image image4 = 3 + image;
    thrust::device_vector<float> image4_data = image4.GetData();
    for (int i = 0; i < num_disp; i++)
    {
        std::cout << "3 + image.data[" << i << "] = " << 3 + image_data[i] << ", image4.data[" << i << "] = " << image4_data[i] << std::endl;
    }

    Image image5 = image / 5;
    thrust::device_vector<float> image5_data = image5.GetData();
    for (int i = 0; i < num_disp; i++)
    {
        std::cout << "image.data[" << i << "] / 5 = " << image_data[i] / 5 << ", image5.data[" << i << "] = " << image5_data[i] << std::endl;
    }

    return 0;
}