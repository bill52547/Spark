//
// Created by Minghao Guo on 2021/2/25.
//

#include <thrust/device_vector.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unistd.h>
#include <iomanip>

using namespace std;
using namespace thrust;

class Vector
{
public:
    Vector() {}
    void SetData(const device_vector<float> data_)
    {
        this->data = data_;
    }


public:
    device_vector<float> data;
};

class Vector2
{
public:
    Vector2() {
        this->data = new device_vector<float>;
    }

    void SetData(const device_vector<float> * data_)
    {
        this->data = data_;
    }

public:
    device_vector<float> * data;
};

int main()
{
    device_vector<float> vec(4);
    vec[0] = 1.f;
    vec[1] = 2.f;
    vec[2] = 3.f;
    vec[3] = 4.f;

    Vector obj_vec1 = Vector();
    obj_vec1.SetData(vec);
    cout << "address for vec is " << &vec << endl;
    cout << "address for obj_vec1.data is " << &obj_vec1.data << endl;
    cout << "values in obj_vec1.data are" << endl;
    for (auto i = 0; i < 4; i ++)
    {
        cout << obj_vec1.data[i] << " ";
        if (i == 4 - 1)
        {cout << endl;}
    }


    Vector2 obj_vec2 = Vector2();
    obj_vec2.SetData(&vec);
    cout << "address for vec is " << &vec << endl;
    cout << "address for obj_vec2.data is " << &obj_vec2.data << endl;
    cout << "values in obj_vec2.data are" << endl;
    for (auto i = 0; i < 4; i ++)
    {
        cout << obj_vec2.data[i] << " ";
        if (i == 4 - 1)
        {cout << endl;}
    }
    return 0;
}