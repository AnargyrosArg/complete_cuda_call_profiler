#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnSpotrsBatched(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, int nrhs, float *A[], int lda, float *B[], int ldb, int *d_info, int batchSize)
{
	cusolverStatus_t retval = cusolverDnSpotrsBatched(handle, uplo, n, nrhs, A, lda, B, ldb, d_info, batchSize);
	return retval;
}