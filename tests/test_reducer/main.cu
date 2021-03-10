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
#include "include/reduce.h"
#include "include/counter.h"
#include "include/arithmetic.h"

int main()
{
    thrust::device_vector<float> vec(4);
    vec[0] = 1.f;
    vec[1] = 2.f;
    vec[2] = 3.f;
    vec[3] = 4.f;

    std::cout << "count 1 = " << count_eq(vec) << std::endl;
    std::cout << "norm2 = " << norm2(vec) << std::endl;
    std::cout << "norm1 = " << norm1(vec) << std::endl;
    std::cout << "norm3 = " << norm(vec, 3.f) << std::endl;
    for (int ind = 0; ind < 4; ind ++)
        std::cout << "pow(2) = " << pow(vec, 2.f)[ind] << std::endl;

    for (int ind = 0; ind < 4; ind ++)
        std::cout << "exp = " << exp(vec)[ind] << std::endl;

    return 0;
}