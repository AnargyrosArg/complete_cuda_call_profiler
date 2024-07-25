#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnIRSParamsDisableFallback(cusolverDnIRSParams_t params)
{
	cusolverStatus_t retval = cusolverDnIRSParamsDisableFallback(params);
	return retval;
}