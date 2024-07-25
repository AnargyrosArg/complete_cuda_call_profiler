#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnSgetrf(cusolverDnHandle_t handle, int m, int n, float *A, int lda, float *Workspace, int *devIpiv, int *devInfo)
{
	cusolverStatus_t retval = cusolverDnSgetrf(handle, m, n, A, lda, Workspace, devIpiv, devInfo);
	return retval;
}