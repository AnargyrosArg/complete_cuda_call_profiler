#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnSgesvdaStridedBatched_bufferSize(cusolverDnHandle_t handle, cusolverEigMode_t jobz, int rank, int m, int n, const float *d_A, int lda, long long int strideA, const float *d_S, long long int strideS, const float *d_U, int ldu, long long int strideU, const float *d_V, int ldv, long long int strideV, int *lwork, int batchSize)
{
	cusolverStatus_t retval = cusolverDnSgesvdaStridedBatched_bufferSize(handle, jobz, rank, m, n, d_A, lda, strideA, d_S, strideS, d_U, ldu, strideU, d_V, ldv, strideV, lwork, batchSize);
	return retval;
}