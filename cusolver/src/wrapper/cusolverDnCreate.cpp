#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnCreate(cusolverDnHandle_t *handle)
{
	cusolverStatus_t retval = cusolverDnCreate(handle);
	return retval;
}