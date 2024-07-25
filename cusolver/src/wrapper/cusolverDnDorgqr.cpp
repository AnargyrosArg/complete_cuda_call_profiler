#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnDorgqr(cusolverDnHandle_t handle, int m, int n, int k, double *A, int lda, const double *tau, double *work, int lwork, int *info)
{
	cusolverStatus_t retval = cusolverDnDorgqr(handle, m, n, k, A, lda, tau, work, lwork, info);
	return retval;
}