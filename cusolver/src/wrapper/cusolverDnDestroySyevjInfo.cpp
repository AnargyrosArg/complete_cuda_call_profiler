#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnDestroySyevjInfo(syevjInfo_t info)
{
	cusolverStatus_t retval = cusolverDnDestroySyevjInfo(info);
	return retval;
}