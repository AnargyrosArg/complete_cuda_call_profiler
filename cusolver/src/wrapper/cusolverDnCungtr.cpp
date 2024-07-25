#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnCungtr(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, cuComplex *A, int lda, const cuComplex *tau, cuComplex *work, int lwork, int *info)
{
	cusolverStatus_t retval = cusolverDnCungtr(handle, uplo, n, A, lda, tau, work, lwork, info);
	return retval;
}