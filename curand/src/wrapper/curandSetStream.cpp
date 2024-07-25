#include <curand.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
curandStatus_t wrapper_curandSetStream(curandGenerator_t generator, cudaStream_t stream)
{
	curandStatus_t retval = curandSetStream(generator, stream);
	return retval;
}