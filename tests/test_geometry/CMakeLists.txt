cmake_minimum_required(VERSION 3.8 FATAL_ERROR)
project(test LANGUAGES CUDA C CXX)
SET(CUDA_NVCC_FLAGS ${CUDA_NVCC_FLAGS} --extended-lambda)

include_directories(../../src)
#set cuda flags


add_executable(
        test
        main.cu
        ../../src/datatype/image.cu
)
target_compile_features(test PUBLIC cxx_std_14)
set_target_properties(
        test
        PROPERTIES
        CUDA_SEPARABLE_COMPILATION ON
)

target_compile_features(test PUBLIC cxx_std_14)
set_property(TARGET test PROPERTY BUILD_RPATH ${CMAKE_CUDA_IMPLICIT_LINK_DIRECTORIES})
