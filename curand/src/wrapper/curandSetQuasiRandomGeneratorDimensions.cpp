#include <curand.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
curandStatus_t wrapper_curandSetQuasiRandomGeneratorDimensions(curandGenerator_t generator, unsigned int num_dimensions)
{
	curandStatus_t retval = curandSetQuasiRandomGeneratorDimensions(generator, num_dimensions);
	return retval;
}