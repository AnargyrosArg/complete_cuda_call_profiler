#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnCgesvd_bufferSize(cusolverDnHandle_t handle, int m, int n, int *lwork)
{
	cusolverStatus_t retval = cusolverDnCgesvd_bufferSize(handle, m, n, lwork);
	return retval;
}