#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnSsytri_bufferSize(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, float *A, int lda, const int *ipiv, int *lwork)
{
	cusolverStatus_t retval = cusolverDnSsytri_bufferSize(handle, uplo, n, A, lda, ipiv, lwork);
	return retval;
}