#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnIRSParamsSetMaxItersInner(cusolverDnIRSParams_t params, cusolver_int_t maxiters_inner)
{
	cusolverStatus_t retval = cusolverDnIRSParamsSetMaxItersInner(params, maxiters_inner);
	return retval;
}