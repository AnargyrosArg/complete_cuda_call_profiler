#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnDgesvd_bufferSize(cusolverDnHandle_t handle, int m, int n, int *lwork)
{
	cusolverStatus_t retval = cusolverDnDgesvd_bufferSize(handle, m, n, lwork);
	return retval;
}