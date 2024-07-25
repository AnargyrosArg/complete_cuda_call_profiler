#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnSpotri_bufferSize(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, float *A, int lda, int *lwork)
{
	cusolverStatus_t retval = cusolverDnSpotri_bufferSize(handle, uplo, n, A, lda, lwork);
	return retval;
}