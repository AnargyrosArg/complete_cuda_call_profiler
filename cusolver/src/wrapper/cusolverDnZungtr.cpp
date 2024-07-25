#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnZungtr(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, cuDoubleComplex *A, int lda, const cuDoubleComplex *tau, cuDoubleComplex *work, int lwork, int *info)
{
	cusolverStatus_t retval = cusolverDnZungtr(handle, uplo, n, A, lda, tau, work, lwork, info);
	return retval;
}