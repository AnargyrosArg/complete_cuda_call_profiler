#include <curand.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
curandStatus_t wrapper_curandGenerateSeeds(curandGenerator_t generator)
{
	curandStatus_t retval = curandGenerateSeeds(generator);
	return retval;
}