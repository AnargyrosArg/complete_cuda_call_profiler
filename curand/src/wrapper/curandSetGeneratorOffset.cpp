#include <curand.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
curandStatus_t wrapper_curandSetGeneratorOffset(curandGenerator_t generator, unsigned long long offset)
{
	curandStatus_t retval = curandSetGeneratorOffset(generator, offset);
	return retval;
}