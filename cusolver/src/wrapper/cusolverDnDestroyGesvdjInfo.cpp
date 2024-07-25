#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnDestroyGesvdjInfo(gesvdjInfo_t info)
{
	cusolverStatus_t retval = cusolverDnDestroyGesvdjInfo(info);
	return retval;
}