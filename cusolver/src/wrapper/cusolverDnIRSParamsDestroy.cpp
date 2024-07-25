#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnIRSParamsDestroy(cusolverDnIRSParams_t params)
{
	cusolverStatus_t retval = cusolverDnIRSParamsDestroy(params);
	return retval;
}