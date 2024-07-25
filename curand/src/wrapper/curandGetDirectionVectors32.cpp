#include <curand.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
curandStatus_t wrapper_curandGetDirectionVectors32(curandDirectionVectors32_t *vectors[], curandDirectionVectorSet_t set)
{
	curandStatus_t retval = curandGetDirectionVectors32(vectors, set);
	return retval;
}