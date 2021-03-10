//
// Created by Minghao Guo on 2021/2/25.
//

#include <thrust/device_vector.h>
#include <thrust/sequence.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unistd.h>
#include <iomanip>
#include <thrust/functional.h>
#include "datatype/image.h"
#include "datatype/listmode.h"
#include "datatype/LineOfResponse.h"
#include "../../src/geometry/PitechCylinder.h"
#include "../../src/geometry/Lut.h"
#include "../../src/functions/BackProjector.h"
#include "../../src/helpers/tqdm.h"
#include <thrust/reduce.h>

using namespace std;
using namespace thrust;

int main()
{
    cout << "Loading lut \n";
    string filename = "/home/bill52547/Workspace/SRF_NEF_cuda/tests/test_load_pos/build/pos_raw.bin";
    PosLutBoundary lut = PosLutBoundary::read_raw(filename);
    device_vector<float> affine_data(16);
    affine_data[0] = 400.f; affine_data[5] = 400.f; affine_data[10] = 400.f;
    device_vector<float> image_data(200 * 200 * 200);
    Image emap = {{200, 200, 200}, affine_data, image_data};
    BackProjector bp = {-1.f, emap};
    PitechCylinder scanner_20panel;
    cout << "Generating Standard Listmode: \n";
    tqdm bar;
    for (int iPanel = 0; iPanel < scanner_20panel.nPanel; ++iPanel)
    {
        for (int iPanel2 = 0; iPanel2 < scanner_20panel.nPanel; ++iPanel2)
        {
            if (iPanel == iPanel2) {continue;}
            int n_cry = scanner_20panel.nCryPerPanel();
            device_vector<unsigned short> index1(n_cry * n_cry);
            device_vector<unsigned short> index2(n_cry * n_cry);
            for (int icry = 0; icry < n_cry; ++icry)
                thrust::sequence(index1.begin() + n_cry * icry,
                                 index1.begin() + n_cry * (icry + 1),
                                 iPanel * scanner_20panel.nCryPerPanel());
            for (int icry = 0; icry < n_cry; ++icry)
                thrust::fill(index2.begin() + n_cry * icry,
                             index2.begin() + n_cry * (icry + 1),
                             iPanel2 * scanner_20panel.nCryPerPanel() + icry);

            LineOfResponse lor = {index1, index2};
            device_vector<float> lut_data = lut.data;
            lor.SetLutPos(lut_data);
            Listmode listmode = {lor, 1.f};
            emap = emap + bp(listmode);
        }
        bar.progress(iPanel, scanner_20panel.nPanel);
    }
    bar.finish();
    string out_path = "emap.bin";
    emap.write(out_path);
    return 0;
}