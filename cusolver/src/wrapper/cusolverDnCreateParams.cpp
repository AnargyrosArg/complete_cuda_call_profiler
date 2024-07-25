#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnCreateParams(cusolverDnParams_t *params)
{
	cusolverStatus_t retval = cusolverDnCreateParams(params);
	return retval;
}