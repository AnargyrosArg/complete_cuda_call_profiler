#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnSpotrf_bufferSize(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, float *A, int lda, int *Lwork)
{
	cusolverStatus_t retval = cusolverDnSpotrf_bufferSize(handle, uplo, n, A, lda, Lwork);
	return retval;
}