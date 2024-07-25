#include <curand.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
curandStatus_t wrapper_curandGenerateUniformDouble(curandGenerator_t generator, double *outputPtr, size_t num)
{
	curandStatus_t retval = curandGenerateUniformDouble(generator, outputPtr, num);
	return retval;
}