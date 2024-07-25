#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnSorgtr_bufferSize(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, const float *A, int lda, const float *tau, int *lwork)
{
	cusolverStatus_t retval = cusolverDnSorgtr_bufferSize(handle, uplo, n, A, lda, tau, lwork);
	return retval;
}