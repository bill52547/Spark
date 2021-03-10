//
// Created by Minghao Guo on 2021/3/5.
//

#include "BackProjector.h"
#include "../config/config.h"
#include <iostream>

#define ABS(x) ((x > 0) ? x : -(x))
#define MAX(a, b) (((a) > (b)) ? a : b)
#define MIN(a, b) (((a) < (b)) ? a : b)
const float PI = 3.1415926;
const float eps_ = 0.00443;
#define IndexType LOR_INDEX_TYPE
#define numCry MAX_CRYSTAL_ID
#include "../helpers/cuda_safe_call.h"
struct DImage
{
    int nx, ny, nz;
    float *affine;
    float *data;
};

struct DListmode
{
    int num;
    float *data;
    IndexType *index1;
    IndexType *index2;
    float *time_diff;
    float *lut_cry;
};

__device__
float cal_dist(const float x1, const float y1, const float z1,
                          const float x2, const float y2, const float z2) {
    return (float)sqrtf((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) +
                        (z1 - z2) * (z1 - z2));
}

__device__ void
backproject_device(float *image, const float vproj, const float x1l,
                   const float x1r, const float y1l, const float y1r,
                   const float z1b, const float z1f, const float x2l,
                   const float x2r, const float y2l, const float y2r,
                   const float z2b, const float z2f,
                   const int nx, const int ny, const int nz,
                   const float dx, const float dy, const float dz,
                   const float tof_value, const float tof_resolution) {
    const float x1c = (x1l + x1r) / 2;
    const float y1c = (y1l + y1r) / 2;
    const float z1c = (z1f + z1b) / 2;
    const float x2c = (x2l + x2r) / 2;
    const float y2c = (y2l + y2r) / 2;
    const float z2c = (z2f + z2b) / 2;

    const float tof_sigma = tof_resolution / 2.355 * 0.3 / 2;
    const float over_tof_sigma2 = 0.5 / tof_sigma / tof_sigma;
    const float over_sqrt_2pi_tof_sigma2 =
            1 / sqrt(2.0 * PI * tof_sigma * tof_sigma);
    const float L = cal_dist(x1c, y1c, z1c, x2c, y2c, z2c);
    const float ratio1 = (1.0 - tof_value * 0.3 / L) / 2;
    float tof_weight;
//
    if (ABS(x1c - x2c) > ABS(y1c - y2c)) {
        float tan_alpha = (y1c - y2c) / (x1c - x2c);
        float tan_gamma = (z1c - z2c) / (x1c - x2c);
        float inv_cos_alpha = (float)sqrtf(1 + tan_alpha * tan_alpha);
        float inv_cos_gamma = (float)sqrtf(1 + tan_gamma * tan_gamma);
        for (int ix = 0; ix < nx; ix++) {
            float xc, ratio, cylr, cyrl, czb, czf, yi1, yi2, zi1, zi2;
            int Yi1, Yi2, Zi1, Zi2;
            xc = ((float)ix + 0.5f - (float)nx / 2) * dx;
            float weight = inv_cos_gamma * inv_cos_alpha;
            // float weight = 1;
            if (tof_sigma > 0) {
                float d2_tof = ((xc - x1c) / (x2c - x1c) - ratio1) * L;
                float t2 = -d2_tof * d2_tof * over_tof_sigma2;
                tof_weight =
                        __expf(t2) * over_sqrt_2pi_tof_sigma2 * dx * L / ABS(x1c - x2c);
                if (tof_weight < eps_) {
                    continue;
                }
                weight *= tof_weight;
            }
            ratio = (y2r - y1l) / (x2r - x1l);
            cylr = ratio * (xc - x1l) + y1l + ny / 2 * dy;

            ratio = (y2l - y1r) / (x2l - x1r);
            cyrl = ratio * (xc - x1r) + y1r + ny / 2 * dy;

            yi1 = MIN(cyrl, cylr);
            Yi1 = (int)floorf(yi1 / dy);
            yi2 = MAX(cyrl, cylr);
            Yi2 = (int)floorf(yi2 / dy);

            ratio = (z2b - z1b) / (x2c - x1c);
            czb = ratio * (xc - x1c) + z1b + nz / 2 * dz;
            ratio = (z2f - z1f) / (x2c - x1c);
            czf = ratio * (xc - x1c) + z1f + nz / 2 * dz;

            zi1 = MIN(czb, czf);
            Zi1 = (int)floorf(zi1 / dz);
            zi2 = MAX(czb, czf);
            Zi2 = (int)floorf(zi2 / dz);
            float wy, wz;
            for (int iy = MAX(0, Yi1); iy <= MIN(ny - 1, Yi2); iy++)
            {
                wy = MIN((iy + 1.0f) * dy, yi2) - MAX((iy + 0.0f) * dy, yi1);
                wy /= (yi2 - yi1);
                for (int iz = MAX(0, Zi1); iz <= MIN(nz - 1, Zi2); iz++) {
                    wz = MIN((iz + 1.0f) * dz, zi2) - MAX((iz + 0.0f) * dz, zi1);
                    wz /= (zi2 - zi1);
                    if (iy >= 0 && iy < ny && iz >= 0 && iz < nz)
                        atomicAdd(image + ix + iy * nx + iz * nx * ny,
                                  vproj * wy * wz * weight);
                }
            }
        }
    } else {
        float tan_alpha = (x1c - x2c) / (y1c - y2c);
        float tan_gamma = (z1c - z2c) / (y1c - y2c);
        float inv_cos_alpha = (float)sqrtf(1 + tan_alpha * tan_alpha);
        float inv_cos_gamma = (float)sqrtf(1 + tan_gamma * tan_gamma);
        for (int iy = 0; iy < ny; iy++) {
            float yc, ratio, cxlr, cxrl, czb, czf, xi1, xi2, zi1, zi2;
            int Xi1, Xi2, Zi1, Zi2;
            yc = ((float)iy + 0.5f - (float)ny / 2) * dy;
            float weight = inv_cos_gamma * inv_cos_alpha;
            if (tof_sigma > 0) {
                float d2_tof = ((yc - y1c) / (y2c - y1c) - ratio1) * L;
                float t2 = -d2_tof * d2_tof * over_tof_sigma2;
                tof_weight =
                        __expf(t2) * over_sqrt_2pi_tof_sigma2 * dy * L / ABS(y1c - y2c);
                if (tof_weight < eps_) {
                    continue;
                }
                weight *= tof_weight;
            }
            ratio = (x2r - x1l) / (y2r - y1l);
            cxlr = ratio * (yc - y1l) + x1l + nx / 2 * dx;

            ratio = (x2l - x1r) / (y2l - y1r);
            cxrl = ratio * (yc - y1r) + x1r + nx / 2 * dx;

            xi1 = MIN(cxrl, cxlr);
            Xi1 = (int)floorf(xi1 / dx);
            xi2 = MAX(cxrl, cxlr);
            Xi2 = (int)floorf(xi2 / dx);

            ratio = (z2b - z1b) / (y2c - y1c);
            czb = ratio * (yc - y1c) + z1b + nz / 2 * dz;
            ratio = (z2f - z1f) / (y2c - y1c);
            czf = ratio * (yc - y1c) + z1f + nz / 2 * dz;

            zi1 = MIN(czb, czf);
            Zi1 = (int)floorf(zi1 / dz);
            zi2 = MAX(czb, czf);
            Zi2 = (int)floorf(zi2 / dz);
            float wx, wz;
            for (int ix = MAX(0, Xi1); ix <= MIN(nx - 1, Xi2); ix++)
            {
                wx = MIN((ix + 1.0f) * dx, xi2) - MAX((ix + 0.0f) * dx, xi1);
                wx /= (xi2 - xi1);
                for (int iz = MAX(0, Zi1); iz <= MIN(nz - 1, Zi2); iz++) {
                    wz = MIN((iz + 1.0f) * dz, zi2) - MAX((iz + 0.0f) * dz, zi1);
                    wz /= (zi2 - zi1);
                        atomicAdd(image + ix + iy * nx + iz * nx * ny,
                              vproj * wx * wz * weight);
                }
            }
        }
    }
}

__global__ void bproject(DImage image,
        const DListmode listmode,
        const float ctr = -1.f)
{
    int step = blockDim.x * gridDim.x;

    for (int tid = blockIdx.x * blockDim.x + threadIdx.x;
    tid < (listmode.num + step); tid += step) {
        if (tid >= listmode.num) {
            return;
        }
        const int nx = image.nx, ny = image.ny, nz = image.nz;
        const float dx = image.affine[0] / nx, dy = image.affine[5] / ny, dz = image.affine[10] / nz;
        const float cx = image.affine[4], cy = image.affine[8], cz = image.affine[12];
        int id1 = listmode.index1[tid], id2 = listmode.index2[tid];
        float time_diff_ = 0.f;
        if (ctr > 0) {time_diff_ = listmode.time_diff[tid];}
        if (tid >= nx * ny * nz) {return;}
        backproject_device(image.data,
                listmode.data[tid],
                listmode.lut_cry[id1 + 0 * numCry] + cx,
                listmode.lut_cry[id1 + 3 * numCry] + cx,
                listmode.lut_cry[id1 + 1 * numCry] + cy,
                listmode.lut_cry[id1 + 4 * numCry] + cy,
                listmode.lut_cry[id1 + 2 * numCry] + cz,
                listmode.lut_cry[id1 + 5 * numCry] + cz,
                listmode.lut_cry[id2 + 0 * numCry] + cx,
                listmode.lut_cry[id2 + 3 * numCry] + cx,
                listmode.lut_cry[id2 + 1 * numCry] + cy,
                listmode.lut_cry[id2 + 4 * numCry] + cy,
                listmode.lut_cry[id2 + 2 * numCry] + cz,
                listmode.lut_cry[id2 + 5 * numCry] + cz,
                nx, ny, nz, dx, dy, dz,
                time_diff_,
                ctr);
    }
}


Image BackProjector::operator() (Listmode & listmode)
{
    device_vector<float> out_data(this->image_template.GetDataNumber());
    DImage d_image = {this->image_template.GetShape().x,
                       this->image_template.GetShape().y,
                       this->image_template.GetShape().z,
                       thrust::raw_pointer_cast(this->image_template.GetAffine().data.data()),
                       thrust::raw_pointer_cast(out_data.data())};

    DListmode d_listmode = {
        listmode.GetNum(),
        listmode.GetDataRawPtr(),
        listmode.GetIndex1RawPtr(),
        listmode.GetIndex2RawPtr(),
        listmode.GetTimeDiffRawPtr(),
        listmode.GetLutPosRawPtr()
    };

    float *out_data_ptr = raw_pointer_cast(out_data.data());
    bproject<<<listmode.GetNum() / 512 + 1 ,512>>>(d_image, d_listmode, this->CTR);
    CHECK_LAUNCH_ERROR();
    return this->image_template.UpdateData(out_data);
}
