#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnZsytri(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, cuDoubleComplex *A, int lda, const int *ipiv, cuDoubleComplex *work, int lwork, int *info)
{
	cusolverStatus_t retval = cusolverDnZsytri(handle, uplo, n, A, lda, ipiv, work, lwork, info);
	return retval;
}