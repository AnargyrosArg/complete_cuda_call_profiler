#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnSorgqr(cusolverDnHandle_t handle, int m, int n, int k, float *A, int lda, const float *tau, float *work, int lwork, int *info)
{
	cusolverStatus_t retval = cusolverDnSorgqr(handle, m, n, k, A, lda, tau, work, lwork, info);
	return retval;
}