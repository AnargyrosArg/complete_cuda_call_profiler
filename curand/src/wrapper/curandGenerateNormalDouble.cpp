#include <curand.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
curandStatus_t wrapper_curandGenerateNormalDouble(curandGenerator_t generator, double *outputPtr, size_t n, double mean, double stddev)
{
	curandStatus_t retval = curandGenerateNormalDouble(generator, outputPtr, n, mean, stddev);
	return retval;
}