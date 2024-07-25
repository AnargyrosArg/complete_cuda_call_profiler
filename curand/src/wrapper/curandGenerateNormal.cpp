#include <curand.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
curandStatus_t wrapper_curandGenerateNormal(curandGenerator_t generator, float *outputPtr, size_t n, float mean, float stddev)
{
	curandStatus_t retval = curandGenerateNormal(generator, outputPtr, n, mean, stddev);
	return retval;
}