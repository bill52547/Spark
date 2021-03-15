//
// Created by Minghao Guo on 2021/3/4.
//

#ifndef INCLUDE_CONFIG_H
#define INCLUDE_CONFIG_H

// setting up LineOfResponse attribute
#define LOR_INDEX_TYPE unsigned short
#define LOR_WITH_INDEX 1
#define LOR_WITH_TIME_DIFF 0
#define LOR_WITH_POS 1 - LOR_WITH_INDEX
#define LOR_WITH_TABLE_Z 0
#define LOR_WITH_ENERGY 0

#define LOR_MIN_GAP 100
#define LOR_MAX_Z_GAP 10000
#define LOR_TIME_WIN 2000

#define ENERGY_LOW 435
#define ENERGY_HIGH 585

#define MAX_CRYSTAL_ID 34560

#define DEFAULT_CTR 300

#define DEFAULT_H5_DSETNAME "dset"
#endif //INCLUDE_CONFIG_H
