#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnDgetrf(cusolverDnHandle_t handle, int m, int n, double *A, int lda, double *Workspace, int *devIpiv, int *devInfo)
{
	cusolverStatus_t retval = cusolverDnDgetrf(handle, m, n, A, lda, Workspace, devIpiv, devInfo);
	return retval;
}