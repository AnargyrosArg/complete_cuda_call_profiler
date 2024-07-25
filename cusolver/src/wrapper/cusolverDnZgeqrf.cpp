#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnZgeqrf(cusolverDnHandle_t handle, int m, int n, cuDoubleComplex *A, int lda, cuDoubleComplex *TAU, cuDoubleComplex *Workspace, int Lwork, int *devInfo)
{
	cusolverStatus_t retval = cusolverDnZgeqrf(handle, m, n, A, lda, TAU, Workspace, Lwork, devInfo);
	return retval;
}