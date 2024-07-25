#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnIRSParamsGetMaxIters(cusolverDnIRSParams_t params, cusolver_int_t *maxiters)
{
	cusolverStatus_t retval = cusolverDnIRSParamsGetMaxIters(params, maxiters);
	return retval;
}