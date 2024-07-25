#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnDestroy(cusolverDnHandle_t handle)
{
	cusolverStatus_t retval = cusolverDnDestroy(handle);
	return retval;
}