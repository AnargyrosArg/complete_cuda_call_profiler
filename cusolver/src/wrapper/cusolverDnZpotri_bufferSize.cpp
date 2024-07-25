#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnZpotri_bufferSize(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, cuDoubleComplex *A, int lda, int *lwork)
{
	cusolverStatus_t retval = cusolverDnZpotri_bufferSize(handle, uplo, n, A, lda, lwork);
	return retval;
}