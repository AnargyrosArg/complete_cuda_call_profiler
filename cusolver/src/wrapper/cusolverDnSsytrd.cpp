#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnSsytrd(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, float *A, int lda, float *d, float *e, float *tau, float *work, int lwork, int *info)
{
	cusolverStatus_t retval = cusolverDnSsytrd(handle, uplo, n, A, lda, d, e, tau, work, lwork, info);
	return retval;
}