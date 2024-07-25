#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnIRSParamsSetMaxIters(cusolverDnIRSParams_t params, cusolver_int_t maxiters)
{
	cusolverStatus_t retval = cusolverDnIRSParamsSetMaxIters(params, maxiters);
	return retval;
}