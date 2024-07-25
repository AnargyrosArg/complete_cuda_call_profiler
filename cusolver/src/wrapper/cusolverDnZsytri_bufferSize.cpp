#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnZsytri_bufferSize(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, cuDoubleComplex *A, int lda, const int *ipiv, int *lwork)
{
	cusolverStatus_t retval = cusolverDnZsytri_bufferSize(handle, uplo, n, A, lda, ipiv, lwork);
	return retval;
}