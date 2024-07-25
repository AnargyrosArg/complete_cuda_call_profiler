#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnSsytrd_bufferSize(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, const float *A, int lda, const float *d, const float *e, const float *tau, int *lwork)
{
	cusolverStatus_t retval = cusolverDnSsytrd_bufferSize(handle, uplo, n, A, lda, d, e, tau, lwork);
	return retval;
}