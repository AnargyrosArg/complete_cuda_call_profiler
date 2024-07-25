#include <curand.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
curandStatus_t wrapper_curandCreatePoissonDistribution(double lambda, curandDiscreteDistribution_t *discrete_distribution)
{
	curandStatus_t retval = curandCreatePoissonDistribution(lambda, discrete_distribution);
	return retval;
}