#include <curand.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
curandStatus_t wrapper_curandDestroyGenerator(curandGenerator_t generator)
{
	curandStatus_t retval = curandDestroyGenerator(generator);
	return retval;
}