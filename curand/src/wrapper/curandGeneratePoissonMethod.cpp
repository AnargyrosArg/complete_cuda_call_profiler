#include <curand.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
curandStatus_t wrapper_curandGeneratePoissonMethod(curandGenerator_t generator, unsigned int *outputPtr, size_t n, double lambda, curandMethod_t method)
{
	curandStatus_t retval = curandGeneratePoissonMethod(generator, outputPtr, n, lambda, method);
	return retval;
}