#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnIRSParamsSetTolInner(cusolverDnIRSParams_t params, double val)
{
	cusolverStatus_t retval = cusolverDnIRSParamsSetTolInner(params, val);
	return retval;
}