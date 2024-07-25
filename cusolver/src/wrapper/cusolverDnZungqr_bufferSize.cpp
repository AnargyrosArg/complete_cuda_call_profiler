#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnZungqr_bufferSize(cusolverDnHandle_t handle, int m, int n, int k, const cuDoubleComplex *A, int lda, const cuDoubleComplex *tau, int *lwork)
{
	cusolverStatus_t retval = cusolverDnZungqr_bufferSize(handle, m, n, k, A, lda, tau, lwork);
	return retval;
}