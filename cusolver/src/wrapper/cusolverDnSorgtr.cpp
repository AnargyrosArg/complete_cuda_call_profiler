#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnSorgtr(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, float *A, int lda, const float *tau, float *work, int lwork, int *info)
{
	cusolverStatus_t retval = cusolverDnSorgtr(handle, uplo, n, A, lda, tau, work, lwork, info);
	return retval;
}