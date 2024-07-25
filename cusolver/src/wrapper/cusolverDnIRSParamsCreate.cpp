#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnIRSParamsCreate(cusolverDnIRSParams_t *params_ptr)
{
	cusolverStatus_t retval = cusolverDnIRSParamsCreate(params_ptr);
	return retval;
}