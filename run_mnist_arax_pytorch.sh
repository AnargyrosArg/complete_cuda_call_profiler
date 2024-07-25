#!/bin/bash

#----------------------------------------------------------------------
#Set this to your "dynamic_cuda" repository path
DYNAMIC_CUDA_PATH=your/path/here

#Set this to your autotalk path
AUTOTALK_PATH=your/path/here

#Set this to the path of the conda environment you created while compiling pytorch
#It should be under <conda_home>/envs/<env_name>
CONDA_ENV_PATH=your/path/here
#----------------------------------------------------------------------

export AUTOTALK_PATH=$AUTOTALK_PATH

#enable JIT
export CUDA_FORCE_PTX_JIT=1

#conda env libraries
export  LD_LIBRARY_PATH="$CONDA_ENV_PATH/lib/":${LD_LIBRARY_PATH}

#Autotalk Runtime + driver Lib
export LD_LIBRARY_PATH="$AUTOTALK_PATH/build/lib64/":${LD_LIBRARY_PATH}

#Fake dynamic CUDA libs
export LD_LIBRARY_PATH="$DYNAMIC_CUDA_PATH/lib/":${LD_LIBRARY_PATH}

LD_PRELOAD="$DYNAMIC_CUDA_PATH/lib/libdlopen.so $DYNAMIC_CUDA_PATH/lib/libcupti.so $DYNAMIC_CUDA_PATH/lib/libcusparse.so $DYNAMIC_CUDA_PATH/lib/libcublasLt.so $DYNAMIC_CUDA_PATH/lib/libcublas.so $DYNAMIC_CUDA_PATH/lib/libcufft.so $DYNAMIC_CUDA_PATH/lib/libcurand.so $DYNAMIC_CUDA_PATH/lib/libcusparse.so" python main.py