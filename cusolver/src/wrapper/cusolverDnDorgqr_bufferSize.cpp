#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnDorgqr_bufferSize(cusolverDnHandle_t handle, int m, int n, int k, const double *A, int lda, const double *tau, int *lwork)
{
	cusolverStatus_t retval = cusolverDnDorgqr_bufferSize(handle, m, n, k, A, lda, tau, lwork);
	return retval;
}