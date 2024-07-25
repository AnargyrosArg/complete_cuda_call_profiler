#include <curand.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
curandStatus_t wrapper_curandGenerate(curandGenerator_t generator, unsigned int *outputPtr, size_t num)
{
	curandStatus_t retval = curandGenerate(generator, outputPtr, num);
	return retval;
}