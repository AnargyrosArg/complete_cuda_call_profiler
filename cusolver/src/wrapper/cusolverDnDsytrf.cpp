#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnDsytrf(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, double *A, int lda, int *ipiv, double *work, int lwork, int *info)
{
	cusolverStatus_t retval = cusolverDnDsytrf(handle, uplo, n, A, lda, ipiv, work, lwork, info);
	return retval;
}