#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnSgesvdjBatched_bufferSize(cusolverDnHandle_t handle, cusolverEigMode_t jobz, int m, int n, const float *A, int lda, const float *S, const float *U, int ldu, const float *V, int ldv, int *lwork, gesvdjInfo_t params, int batchSize)
{
	cusolverStatus_t retval = cusolverDnSgesvdjBatched_bufferSize(handle, jobz, m, n, A, lda, S, U, ldu, V, ldv, lwork, params, batchSize);
	return retval;
}