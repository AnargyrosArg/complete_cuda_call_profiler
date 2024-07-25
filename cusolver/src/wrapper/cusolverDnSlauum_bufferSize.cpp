#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnSlauum_bufferSize(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, float *A, int lda, int *lwork)
{
	cusolverStatus_t retval = cusolverDnSlauum_bufferSize(handle, uplo, n, A, lda, lwork);
	return retval;
}