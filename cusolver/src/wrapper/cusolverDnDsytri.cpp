#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnDsytri(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, double *A, int lda, const int *ipiv, double *work, int lwork, int *info)
{
	cusolverStatus_t retval = cusolverDnDsytri(handle, uplo, n, A, lda, ipiv, work, lwork, info);
	return retval;
}