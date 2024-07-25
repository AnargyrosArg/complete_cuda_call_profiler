#include <curand.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
curandStatus_t wrapper_curandGeneratePoisson(curandGenerator_t generator, unsigned int *outputPtr, size_t n, double lambda)
{
	curandStatus_t retval = curandGeneratePoisson(generator, outputPtr, n, lambda);
	return retval;
}