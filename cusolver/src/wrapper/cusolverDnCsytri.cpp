#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnCsytri(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, cuComplex *A, int lda, const int *ipiv, cuComplex *work, int lwork, int *info)
{
	cusolverStatus_t retval = cusolverDnCsytri(handle, uplo, n, A, lda, ipiv, work, lwork, info);
	return retval;
}