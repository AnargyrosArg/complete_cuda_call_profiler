#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnDgesvdaStridedBatched(cusolverDnHandle_t handle, cusolverEigMode_t jobz, int rank, int m, int n, const double *d_A, int lda, long long int strideA, double *d_S, long long int strideS, double *d_U, int ldu, long long int strideU, double *d_V, int ldv, long long int strideV, double *d_work, int lwork, int *d_info, double *h_R_nrmF, int batchSize)
{
	cusolverStatus_t retval = cusolverDnDgesvdaStridedBatched(handle, jobz, rank, m, n, d_A, lda, strideA, d_S, strideS, d_U, ldu, strideU, d_V, ldv, strideV, d_work, lwork, d_info, h_R_nrmF, batchSize);
	return retval;
}