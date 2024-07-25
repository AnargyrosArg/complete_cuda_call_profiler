#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnZungqr(cusolverDnHandle_t handle, int m, int n, int k, cuDoubleComplex *A, int lda, const cuDoubleComplex *tau, cuDoubleComplex *work, int lwork, int *info)
{
	cusolverStatus_t retval = cusolverDnZungqr(handle, m, n, k, A, lda, tau, work, lwork, info);
	return retval;
}