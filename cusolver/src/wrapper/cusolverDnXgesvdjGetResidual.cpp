#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnXgesvdjGetResidual(cusolverDnHandle_t handle, gesvdjInfo_t info, double *residual)
{
	cusolverStatus_t retval = cusolverDnXgesvdjGetResidual(handle, info, residual);
	return retval;
}