#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnCreateGesvdjInfo(gesvdjInfo_t *info)
{
	cusolverStatus_t retval = cusolverDnCreateGesvdjInfo(info);
	return retval;
}