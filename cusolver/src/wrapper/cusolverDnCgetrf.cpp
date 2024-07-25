#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnCgetrf(cusolverDnHandle_t handle, int m, int n, cuComplex *A, int lda, cuComplex *Workspace, int *devIpiv, int *devInfo)
{
	cusolverStatus_t retval = cusolverDnCgetrf(handle, m, n, A, lda, Workspace, devIpiv, devInfo);
	return retval;
}