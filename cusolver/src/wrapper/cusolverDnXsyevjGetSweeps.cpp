#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnXsyevjGetSweeps(cusolverDnHandle_t handle, syevjInfo_t info, int *executed_sweeps)
{
	cusolverStatus_t retval = cusolverDnXsyevjGetSweeps(handle, info, executed_sweeps);
	return retval;
}