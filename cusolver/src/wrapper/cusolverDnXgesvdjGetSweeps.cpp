#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnXgesvdjGetSweeps(cusolverDnHandle_t handle, gesvdjInfo_t info, int *executed_sweeps)
{
	cusolverStatus_t retval = cusolverDnXgesvdjGetSweeps(handle, info, executed_sweeps);
	return retval;
}