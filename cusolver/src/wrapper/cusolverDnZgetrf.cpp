#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnZgetrf(cusolverDnHandle_t handle, int m, int n, cuDoubleComplex *A, int lda, cuDoubleComplex *Workspace, int *devIpiv, int *devInfo)
{
	cusolverStatus_t retval = cusolverDnZgetrf(handle, m, n, A, lda, Workspace, devIpiv, devInfo);
	return retval;
}