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

int main()
{
    timer t;
    Shape shape = Shape(32, 32, 32);
    vec_float rand_ = normal_random<float>(shape.x * shape.y * shape.z, 0, 1);
    Image image = Image(shape, Affine(), rand_);
    for (int i = 0; i < 10; i++)
    {
        std::cout << image.GetData()[i] << " ";
    }
    std::cout << "\n";

//    image = image.UpdateData(rand_);
    std::cout << "image.shape = \n";
    Shape shape_ = image.GetShape();
    std::cout << shape_ << std::endl;

    Affine affine_ = image.GetAffine();
    std::cout << "image.affine = \n";
    std::cout << affine_ << std::endl;

    std::cout << "\n";
    std::string filename = "test.bin";
    t.restart();
    image.write(filename);
    printf("saving image with %d %d %d", shape.x, shape.y, shape.z);
    t.display();

    t.restart();
    Image image2 = Image::read(filename);
    printf("loading image with %d %d %d", shape.x, shape.y, shape.z);
    t.display();
    std::cout << "image2.shape = \n";
    Shape shape2_ = image2.GetShape();
    std::cout << shape2_ << std::endl;

    std::cout << "image2.affine = \n";
    Affine affine2_ = image2.GetAffine();
    std::cout << affine2_ << std::endl;

    std::cout << "\n\n\n";
    std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(2);
    thrust::device_vector<float> image_data = image.GetData(), image2_data = image2.GetData();
    tqdm bar;
    for (int i = 0; i < shape.x * shape.y * shape.z; i++)
    {
        if (!image_data[i] == image2_data[i])
        {
            std::cout << "image.data[" << i << "] = " << image_data[i] << ", image2.data[" << i << "] = " << image2_data[i] << std::endl;
            break;
        }
        if (i == shape.x * shape.y * shape.z - 1)
        {
            std::cout << "All equal" << std::endl;
        }
        bar.progress(i, shape.x * shape.y * shape.z);
    }
    bar.finish();
    for (int i = 0; i < 10; i++)
    {
        std::cout << "image.data[" << i << "] = " << image_data[i] << ", image2.data[" << i << "] = " << image2_data[i] << std::endl;
    }
    return 0;
}