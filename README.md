# Complete CUDA call Interception
This project consists of a set of libraries that can be preloaded into any application in order to intercept CUDA calls made by both the application and the underlying CUDA libraries it links with. It is built specifically for CUDA 11.7 .


# Compiling 
To compile this project simply run:

    make

In the root directory of the repo. You can find the result binaries in ./lib

This project is exclusively built and tested for CUDA v11.7


# Running an executable with the tool
In the main directory of this repository there is a script called runner.sh.

1. Modify the runner.sh script and set the TARGET_EXECUTABLE environment variable to the CLI command of the executable you want to run
    
    e.g. TARGET_EXECUTABLE=python ~/main.py
2. Ensure that the runner script is executable
    
    chmod +x runner.sh

3. Run the script

    ./runner.sh



# CUDA RT Interception
Most dynamic CUDA-toolkit libraries (e.g libcublas.so libcusparse.so) are statically linked with a version of cudart.
This means that indirect calls to cudart functions made from within those "higher-level" libraries cannot be intercepted using the traditional preloading trick.
On the other hand static CUDA libraries are compiled to use the shared version of cudart.

In order to completely intercept the CUDA toolkit **trasparently** we create a fake set of CUDA toolkit shared libraries that forward their calls to the static version of the library which will in turn make calls to the shared version of the cudart library.

# CUDA DRV Interception
The cuda driver API library (libcuda.so) is provided by nvidia exclusively as a shared library.
libcuda.so is loaded by higher level libraries through the use of dlopen and dlsym calls. 
This is an issue as the higher level libraries obtain pointers to the functions we want to intercept and call them directly, bypassing our interception.
We further intercept calls to dlopen and dlsym and treat the loading of libcuda.so as a special case, instead returning the handle of our intercept library.

# Hidden CUDA API 
The cuda driver and cuda runtime libraries expose a cuGetExportTable and cudaGetExportTable function respectivelly. 
This function takes a 16-byte UUID as an arguement and returns a table of function pointers internal to the cuda driver library.
These functions are completely undocumented and it is almost impossible to know their arguements without extensive reverse engineering.

These functions are not an issue most of the time, but can become problematic when trying to implement remote function calls.
Through testing we have found out that a subset of those functions, specifically those requested by libraries higher in level than cudart (cublas cudnn etc), can be safely ignored (replaced with a function that returns success) without affecting program validity. 




# Dynamic wrapper libraries to CUDA-11.7 static libraries

We replace each CUDA libX.so library with 2 of our own:

    libX.so
    libwrapper_X.so

Our libX.so is a front-end wrapper to the libwrapper_X.so library

The libX_wrapper.so library is a wrapper to the respective CUDA libX_static.a library 
