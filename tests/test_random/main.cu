//
// Created by Minghao Guo on 2021/2/25.
//

#include <thrust/device_vector.h>
#include "../../src/helpers/random_generator.h"
#include "../../src/helpers/timer.h"
#include <iostream>

using namespace std;
int main()
{
    const int num = 1000;
    timer t;
    auto vec = normal_random<float>(num);

    cout << "with " << num << " random generate" << endl;
    t.display();

    const int num2 = 10000000;
    timer t2;
    auto vec2 = normal_random<float>(num2);
    cout << "with " << num2 << " random generate" << endl;
    t2.display();

}