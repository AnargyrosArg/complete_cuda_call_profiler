#include <curand.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
curandStatus_t wrapper_curandGenerateBinomialMethod(curandGenerator_t generator, unsigned int *outputPtr, size_t num, unsigned int n, double p, curandMethod_t method)
{
	curandStatus_t retval = curandGenerateBinomialMethod(generator, outputPtr, num, n, p, method);
	return retval;
}