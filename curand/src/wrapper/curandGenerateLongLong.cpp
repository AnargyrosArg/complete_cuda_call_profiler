#include <curand.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
curandStatus_t wrapper_curandGenerateLongLong(curandGenerator_t generator, unsigned long long *outputPtr, size_t num)
{
	curandStatus_t retval = curandGenerateLongLong(generator, outputPtr, num);
	return retval;
}