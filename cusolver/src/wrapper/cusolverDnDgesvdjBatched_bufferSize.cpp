#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnDgesvdjBatched_bufferSize(cusolverDnHandle_t handle, cusolverEigMode_t jobz, int m, int n, const double *A, int lda, const double *S, const double *U, int ldu, const double *V, int ldv, int *lwork, gesvdjInfo_t params, int batchSize)
{
	cusolverStatus_t retval = cusolverDnDgesvdjBatched_bufferSize(handle, jobz, m, n, A, lda, S, U, ldu, V, ldv, lwork, params, batchSize);
	return retval;
}