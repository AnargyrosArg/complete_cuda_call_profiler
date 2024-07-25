#include <curand.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
curandStatus_t wrapper_curandSetPseudoRandomGeneratorSeed(curandGenerator_t generator, unsigned long long seed)
{
	curandStatus_t retval = curandSetPseudoRandomGeneratorSeed(generator, seed);
	return retval;
}