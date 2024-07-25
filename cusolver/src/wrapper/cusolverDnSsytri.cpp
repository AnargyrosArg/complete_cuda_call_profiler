#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnSsytri(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, float *A, int lda, const int *ipiv, float *work, int lwork, int *info)
{
	cusolverStatus_t retval = cusolverDnSsytri(handle, uplo, n, A, lda, ipiv, work, lwork, info);
	return retval;
}