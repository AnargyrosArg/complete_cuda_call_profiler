#include <curand.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
curandStatus_t wrapper_curandGetDirectionVectors64(curandDirectionVectors64_t *vectors[], curandDirectionVectorSet_t set)
{
	curandStatus_t retval = curandGetDirectionVectors64(vectors, set);
	return retval;
}