#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnCungqr_bufferSize(cusolverDnHandle_t handle, int m, int n, int k, const cuComplex *A, int lda, const cuComplex *tau, int *lwork)
{
	cusolverStatus_t retval = cusolverDnCungqr_bufferSize(handle, m, n, k, A, lda, tau, lwork);
	return retval;
}