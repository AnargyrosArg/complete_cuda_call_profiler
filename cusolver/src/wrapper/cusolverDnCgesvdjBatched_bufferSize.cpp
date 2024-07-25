#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnCgesvdjBatched_bufferSize(cusolverDnHandle_t handle, cusolverEigMode_t jobz, int m, int n, const cuComplex *A, int lda, const float *S, const cuComplex *U, int ldu, const cuComplex *V, int ldv, int *lwork, gesvdjInfo_t params, int batchSize)
{
	cusolverStatus_t retval = cusolverDnCgesvdjBatched_bufferSize(handle, jobz, m, n, A, lda, S, U, ldu, V, ldv, lwork, params, batchSize);
	return retval;
}