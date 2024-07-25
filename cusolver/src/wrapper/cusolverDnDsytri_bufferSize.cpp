#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnDsytri_bufferSize(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, double *A, int lda, const int *ipiv, int *lwork)
{
	cusolverStatus_t retval = cusolverDnDsytri_bufferSize(handle, uplo, n, A, lda, ipiv, lwork);
	return retval;
}