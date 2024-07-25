#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnZungtr_bufferSize(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, const cuDoubleComplex *A, int lda, const cuDoubleComplex *tau, int *lwork)
{
	cusolverStatus_t retval = cusolverDnZungtr_bufferSize(handle, uplo, n, A, lda, tau, lwork);
	return retval;
}