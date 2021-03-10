//
// Created by Minghao Guo on 2021/2/25.
//

#include <thrust/device_vector.h>
#include "datatype/listmode.h"
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


using namespace std;

int main()
{
    int num = 10;
    Listmode listmode = num;
    for (auto i = 0; i < num; i++)
    {
        cout << i << ": " << listmode.GetIndex1(i) << "\n";
    }

    thrust::device_vector<unsigned short> index1(num), index2(num);
    for (auto i = 0; i < num; i++)
    {
        index1[i] = i * 2;
        index2[i] = i * 3;
    }
    listmode = {index1, index2};
    for (auto i = 0; i < num; i++)
    {
        cout << i << ": index1 = " << listmode.GetIndex1(i) << ", index2 = " << listmode.GetIndex2(i) << "\n";
    }
    cout << "listmode.GetIndex1() = " << listmode.GetIndex1() << endl;
    cout << "listmode.GetIndex1() = " << listmode.GetIndex1() << endl;
    thrust::device_vector<unsigned short> index1_(10);
    thrust::copy(listmode.GetIndex1()->begin(), listmode.GetIndex1()->end(), index1_.begin());
    thrust::device_vector<unsigned short> index1_cp(listmode.GetIndex1()->begin(), listmode.GetIndex1()->end());
    listmode.GetIndex1()->operator[](0) = 20;

//    index1_cp[0] = 20;
    for (auto i = 0; i < num; i++)
    {
        cout << i << ": " << index1_[i] << " " << listmode.GetIndex1(i) << "\n";
    }
    cout << "index1_ address = " << &index1_ << endl;
    cout << "table_z address = " << listmode.GetTableZ() << endl;
    for (auto i = 0; i < num; i++)
    {
        cout << "table_z: " << listmode.GetTableZ(i) << endl;
    }
    listmode.InitialData();
    for (auto i = 0; i < num; i++)
    {
        cout << "data: " << listmode.GetData(i) << endl;
    }
    auto new_data = vec_float(num);
    for (auto i = 0; i < num; i++)
    {
        new_data[i] = i / 2.f;
    }
    Listmode listmode2 = listmode.UpdateData(new_data);
    cout << "listmode.index1 address " << listmode.GetIndex1() << endl;
    cout << "listmode2.index1 address " << listmode2.GetIndex1() << endl;
    cout << "listmode.index1 address " << thrust::raw_pointer_cast(listmode.GetIndex1()->data()) << endl;
    cout << "listmode2.index1 address " << thrust::raw_pointer_cast(listmode2.GetIndex1()->data()) << endl;
    listmode2.GetIndex1()->operator[](0) = 30;

    thrust::device_vector<unsigned short> energy1(num), energy2(num);
    for (auto i = 0; i < num; i++)
    {
        energy1[i] = i;
        energy2[i] = i * 3;
    }
    for (auto i = 0; i < num; i++)
    {
        cout << listmode2.GetEnergy1(i) << " " << listmode2.GetEnergy2(i) << " " << listmode2.InEnergyWindow(i) << endl;
    }
    cout << listmode.GetIndex1(0);
    return 0;
}