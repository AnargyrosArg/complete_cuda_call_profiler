#include <curand.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
curandStatus_t wrapper_curandGenerateBinomial(curandGenerator_t generator, unsigned int *outputPtr, size_t num, unsigned int n, double p)
{
	curandStatus_t retval = curandGenerateBinomial(generator, outputPtr, num, n, p);
	return retval;
}