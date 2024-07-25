#include <curand.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
curandStatus_t wrapper_curandSetGeneratorOrdering(curandGenerator_t generator, curandOrdering_t order)
{
	curandStatus_t retval = curandSetGeneratorOrdering(generator, order);
	return retval;
}