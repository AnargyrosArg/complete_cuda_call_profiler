#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnZgesvdjBatched_bufferSize(cusolverDnHandle_t handle, cusolverEigMode_t jobz, int m, int n, const cuDoubleComplex *A, int lda, const double *S, const cuDoubleComplex *U, int ldu, const cuDoubleComplex *V, int ldv, int *lwork, gesvdjInfo_t params, int batchSize)
{
	cusolverStatus_t retval = cusolverDnZgesvdjBatched_bufferSize(handle, jobz, m, n, A, lda, S, U, ldu, V, ldv, lwork, params, batchSize);
	return retval;
}