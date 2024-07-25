#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnCreateSyevjInfo(syevjInfo_t *info)
{
	cusolverStatus_t retval = cusolverDnCreateSyevjInfo(info);
	return retval;
}