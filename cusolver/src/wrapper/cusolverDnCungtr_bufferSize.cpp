#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnCungtr_bufferSize(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, const cuComplex *A, int lda, const cuComplex *tau, int *lwork)
{
	cusolverStatus_t retval = cusolverDnCungtr_bufferSize(handle, uplo, n, A, lda, tau, lwork);
	return retval;
}