#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnZheevjBatched(cusolverDnHandle_t handle, cusolverEigMode_t jobz, cublasFillMode_t uplo, int n, cuDoubleComplex *A, int lda, double *W, cuDoubleComplex *work, int lwork, int *info, syevjInfo_t params, int batchSize)
{
	cusolverStatus_t retval = cusolverDnZheevjBatched(handle, jobz, uplo, n, A, lda, W, work, lwork, info, params, batchSize);
	return retval;
}