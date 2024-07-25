#include <curand.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
curandStatus_t wrapper_curandDestroyDistribution(curandDiscreteDistribution_t discrete_distribution)
{
	curandStatus_t retval = curandDestroyDistribution(discrete_distribution);
	return retval;
}