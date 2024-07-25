#include <curand.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
curandStatus_t wrapper_curandCreateGenerator(curandGenerator_t *generator, curandRngType_t rng_type)
{
	curandStatus_t retval = curandCreateGenerator(generator, rng_type);
	return retval;
}