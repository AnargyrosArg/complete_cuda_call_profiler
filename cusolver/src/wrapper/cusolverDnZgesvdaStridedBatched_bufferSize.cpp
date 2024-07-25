#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnZgesvdaStridedBatched_bufferSize(cusolverDnHandle_t handle, cusolverEigMode_t jobz, int rank, int m, int n, const cuDoubleComplex *d_A, int lda, long long int strideA, const double *d_S, long long int strideS, const cuDoubleComplex *d_U, int ldu, long long int strideU, const cuDoubleComplex *d_V, int ldv, long long int strideV, int *lwork, int batchSize)
{
	cusolverStatus_t retval = cusolverDnZgesvdaStridedBatched_bufferSize(handle, jobz, rank, m, n, d_A, lda, strideA, d_S, strideS, d_U, ldu, strideU, d_V, ldv, strideV, lwork, batchSize);
	return retval;
}