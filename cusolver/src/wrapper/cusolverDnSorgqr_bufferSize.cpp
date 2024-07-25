#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnSorgqr_bufferSize(cusolverDnHandle_t handle, int m, int n, int k, const float *A, int lda, const float *tau, int *lwork)
{
	cusolverStatus_t retval = cusolverDnSorgqr_bufferSize(handle, m, n, k, A, lda, tau, lwork);
	return retval;
}