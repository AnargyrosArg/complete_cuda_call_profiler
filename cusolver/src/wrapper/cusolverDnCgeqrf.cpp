#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnCgeqrf(cusolverDnHandle_t handle, int m, int n, cuComplex *A, int lda, cuComplex *TAU, cuComplex *Workspace, int Lwork, int *devInfo)
{
	cusolverStatus_t retval = cusolverDnCgeqrf(handle, m, n, A, lda, TAU, Workspace, Lwork, devInfo);
	return retval;
}