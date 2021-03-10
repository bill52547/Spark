//
// Created by Minghao Guo on 2021/2/25.
//

#include <thrust/device_vector.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "helpers/timer.h"
#include <unistd.h>
#include <iomanip>
#include "../../src/geometry/PitechCylinder.h"
#include <thrust/sequence.h>
#include <thrust/transform.h>
#include <thrust/functional.h>
#include "../../src/config/config.h"
#define IndexType LOR_INDEX_TYPE
using namespace std;
using namespace thrust;
using namespace thrust::placeholders;


int main()
{
//    cout << scanner_20panel.inner_radius << " " << M_PI <<  " " << M_PI_2 << endl;
//    cout << scanner_20panel.avgRadius() << endl;
//    cout << scanner_20panel.nCryAll() << endl;
//    cout << scanner_20panel.szSubY() << endl;
//    cout << scanner_20panel.szSubZ() << endl;
//    cout << scanner_20panel.szPicoY() << endl;
//    cout << scanner_20panel.szPicoZ() << endl;
//    cout << scanner_20panel.szPanelY() << endl;
//    cout << scanner_20panel.szPanelZ() << endl;
//    cout << scanner_20panel.gapPicoZ() << endl;

    thrust::device_vector<IndexType> index(scanner_20panel.nCryAll());
    thrust::sequence(index.begin(), index.end());
    int start = 0;

//    thrust::device_vector<IndexType> cry_index(scanner_20panel.nCryAll()),
//                               sub_index(scanner_20panel.nCryAll()),
//                               pico_index(scanner_20panel.nCryAll()),
//                               panel_index(scanner_20panel.nCryAll());
//    cry_index = scanner_20panel.GetCryIndex(index);
//    sub_index = scanner_20panel.GetSubIndex(index);
//    pico_index = scanner_20panel.GetPicoIndex(index);
//    panel_index = scanner_20panel.GetPanelIndex(index);


    thrust::device_vector<IndexType> cry_index = scanner_20panel.GetCryIndex(index),
            cry_index_y = scanner_20panel.GetCryIndexY(index),
            cry_index_z = scanner_20panel.GetCryIndexZ(index),
            sub_index = scanner_20panel.GetSubIndex(index),
            sub_index_y = scanner_20panel.GetSubIndexY(index),
            sub_index_z = scanner_20panel.GetSubIndexZ(index),
            pico_index = scanner_20panel.GetPicoIndex(index),
            pico_index_y = scanner_20panel.GetPicoIndexY(index),
            pico_index_z = scanner_20panel.GetPicoIndexZ(index),
            panel_index = scanner_20panel.GetPanelIndex(index),
            ring_index = scanner_20panel.GetRingIndex(index),
            sector_index = scanner_20panel.GetSectorIndex(index);

//    cout << "index" << ", " << "cry_index" << ", " << "sub_index" << ", " << "pico_index" << ", " << "panel_index" << ", ";
//    cout << "cry_index_y" << ", " << "cry_index_z" << ", " << "sub_index_y" << ", " << "sub_index_z" << ", " << "pico_index_y" << ", " << "pico_index_z" << ", ";
//    cout << "ring_index" << ", " << "sector_index" << endl;
//    for (int i = start; i < start + 20; i++)
//    {
//        cout << index[i] << ", " << cry_index[i] << ", " << sub_index[i] << ", " << pico_index[i] << ", " << panel_index[i] << ", ";
//        cout << cry_index_y[i] << ", " << cry_index_z[i] << ", " << sub_index_y[i] << ", " << sub_index_z[i] << ", " << pico_index_y[i] << ", " << pico_index_z[i] << ", ";
//        cout << ring_index[i] << ", " << sector_index[i] << endl;
//    }

    int nRing = 48, nSec = 720;
//    cout << "ring pos" << endl;
//    for (int i = 0; i < nRing; i++)
//    {
//        cout << scanner_20panel.GetRingPosZ(i) << " ";
//    }

    cout << "pos_x, pos_y\n";
    for (int i = 0; i < nSec; i++)
    {
        cout << scanner_20panel.GetSectorPosX(i) << ", " << scanner_20panel.GetSectorPosY(i) << endl;
    }
    cout << endl;
    return 0;
}