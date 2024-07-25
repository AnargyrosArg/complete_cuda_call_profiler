#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnIRSParamsSetTol(cusolverDnIRSParams_t params, double val)
{
	cusolverStatus_t retval = cusolverDnIRSParamsSetTol(params, val);
	return retval;
}