//
// Created by Minghao Guo on 2021/2/25.
//

#include <thrust/device_vector.h>
#include "../../src/datatype/LineOfResponse.h"
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
#include <thrust/transform.h>
#include <thrust/functional.h>
#include "../../src/config/config.h"

using namespace std;
using namespace thrust;

int main()
{
    const int num = MAX_CRYSTAL_ID;
    LineOfResponse lor = LineOfResponse(num);
    device_vector<unsigned short> index1 = device_vector<unsigned short>(num),
            index2 = device_vector<unsigned short>(num);
    device_vector<float> pos_lut = device_vector<float>(num * 3);
    for (int i = num / 2; i < num; i++)
    {
        pos_lut[i + MAX_CRYSTAL_ID * 0] = 800;
    }
    for (int i = 0; i < num; i++)
    {
        index1[i] = static_cast<unsigned short>(num / 2);
    }
    LineOfResponse lor2 = LineOfResponse(index1, index2);
    lor2.SetLutPos(pos_lut);

    for (int i = 0; i < 20; i++)
    {
        cout << lor2.IsAllGood(i) << " ";
    }

    cout << endl;
    return 0;
}