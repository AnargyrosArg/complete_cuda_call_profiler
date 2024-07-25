#include <curand.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
curandStatus_t wrapper_curandGenerateUniform(curandGenerator_t generator, float *outputPtr, size_t num)
{
	curandStatus_t retval = curandGenerateUniform(generator, outputPtr, num);
	return retval;
}