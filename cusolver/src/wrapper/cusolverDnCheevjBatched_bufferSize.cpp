#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnCheevjBatched_bufferSize(cusolverDnHandle_t handle, cusolverEigMode_t jobz, cublasFillMode_t uplo, int n, const cuComplex *A, int lda, const float *W, int *lwork, syevjInfo_t params, int batchSize)
{
	cusolverStatus_t retval = cusolverDnCheevjBatched_bufferSize(handle, jobz, uplo, n, A, lda, W, lwork, params, batchSize);
	return retval;
}