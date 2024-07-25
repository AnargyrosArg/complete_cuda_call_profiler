#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnIRSParamsEnableFallback(cusolverDnIRSParams_t params)
{
	cusolverStatus_t retval = cusolverDnIRSParamsEnableFallback(params);
	return retval;
}