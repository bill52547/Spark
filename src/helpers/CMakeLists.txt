cmake_minimum_required(VERSION 3.15)
project(helpers CUDA)

set(CMAKE_CUDA_STANDARD 14)

add_library(helpers library.cu library.cuh)

set_target_properties(
        helpers
        PROPERTIES
        CUDA_SEPARABLE_COMPILATION ON)