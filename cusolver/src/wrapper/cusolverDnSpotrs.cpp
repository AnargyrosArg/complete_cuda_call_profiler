#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnSpotrs(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, int nrhs, const float *A, int lda, float *B, int ldb, int *devInfo)
{
	cusolverStatus_t retval = cusolverDnSpotrs(handle, uplo, n, nrhs, A, lda, B, ldb, devInfo);
	return retval;
}