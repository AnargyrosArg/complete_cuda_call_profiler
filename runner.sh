#!/bin/bash

#----------------------------------------------------------------------

TARGET_EXECUTABLE="/path/to/executable"

#Set this to your "dynamic_cuda" repository path
DYNAMIC_CUDA_PATH=your/path/here

#----------------------------------------------------------------------

export DYNAMIC_CUDA_PATH=$DYNAMIC_CUDA_PATH

#Fake dynamic CUDA libs
export LD_LIBRARY_PATH="$DYNAMIC_CUDA_PATH/lib/":${LD_LIBRARY_PATH}

LD_PRELOAD="$DYNAMIC_CUDA_PATH/lib/libdlopen.so $DYNAMIC_CUDA_PATH/lib/libcudart.so $DYNAMIC_CUDA_PATH/lib/libcupti.so $DYNAMIC_CUDA_PATH/lib/libcusparse.so $DYNAMIC_CUDA_PATH/lib/libcublasLt.so $DYNAMIC_CUDA_PATH/lib/libcublas.so $DYNAMIC_CUDA_PATH/lib/libcufft.so $DYNAMIC_CUDA_PATH/lib/libcurand.so $DYNAMIC_CUDA_PATH/lib/libcusparse.so" $TARGET_EXECUTABLE