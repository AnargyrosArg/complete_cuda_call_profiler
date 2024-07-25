# Dynamic wrapper libraries to CUDA-11.7 static libraries

We replace each CUDA libX.so library with 2 of our own:

    libX.so
    libwrapper_X.so

Our libX.so is a front-end wrapper to the libwrapper_X.so library

The libX_wrapper.so library is a wrapper to the respective CUDA libX_static.a library 
# Compilation
In the repository root directory: 
    
    make all -j

This creates a directory ./lib/ that contains symbolic links to each of the front-end libraries.

# Running Pytorch Mnist

1. Compile dynamic_cuda
    
    make all -j

1. Compile and install Arax from the **var_extract branch**

    Instructions in the repo: https://carvgit.ics.forth.gr/accelerators/arax/-/tree/var_extract

1. Compile and install autotalk from the **export_tables branch**

    Instructions in the repo: https://carvgit.ics.forth.gr/accelerators/auto_talk/-/tree/export_tables

1.  Compile and install torch
    
    Instructions in the repo: https://carvgit.ics.forth.gr/manospavl/pytorch_instructions

    **Remember the Conda Home you set.**

    **Make sure to keep the conda environment you created activated**

1. Get python mnist code from https://github.com/pytorch/examples/blob/main/mnist/main.py



1. Configure the ./run_mnist_arax_pytorch.sh script 
    
    - DYNAMIC_CUDA_PATH -> path to this repository
    - AUTOTALK_PATH -> path to autotalk directory
    - CONDA_ENV_PATH -> path to the directory of the conda environment you created while compiling pytorch
    **It should be under <conda_home>/envs/<env_name>**

1. Copy the script over to mnist's directory

1. To run:

    Make sure Arax is running:
    - cd <arax_dir>/build 
    - make run

    Run the script:
    - ./run_mnist_arax_pytorch.sh
    

