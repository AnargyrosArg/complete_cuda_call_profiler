#include <curand.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
curandStatus_t wrapper_curandCreateGeneratorHost(curandGenerator_t *generator, curandRngType_t rng_type)
{
	curandStatus_t retval = curandCreateGeneratorHost(generator, rng_type);
	return retval;
}