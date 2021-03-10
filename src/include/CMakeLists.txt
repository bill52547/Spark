cmake_minimum_required(VERSION 3.15)
project(include CUDA)

set(CMAKE_CUDA_STANDARD 14)

add_executable(include main.cu)

set_target_properties(
        include
        PROPERTIES
        CUDA_SEPARABLE_COMPILATION ON)