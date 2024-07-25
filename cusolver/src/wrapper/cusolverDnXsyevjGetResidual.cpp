#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnXsyevjGetResidual(cusolverDnHandle_t handle, syevjInfo_t info, double *residual)
{
	cusolverStatus_t retval = cusolverDnXsyevjGetResidual(handle, info, residual);
	return retval;
}