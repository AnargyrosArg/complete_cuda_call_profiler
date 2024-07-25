#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnCgesvdjBatched(cusolverDnHandle_t handle, cusolverEigMode_t jobz, int m, int n, cuComplex *A, int lda, float *S, cuComplex *U, int ldu, cuComplex *V, int ldv, cuComplex *work, int lwork, int *info, gesvdjInfo_t params, int batchSize)
{
	cusolverStatus_t retval = cusolverDnCgesvdjBatched(handle, jobz, m, n, A, lda, S, U, ldu, V, ldv, work, lwork, info, params, batchSize);
	return retval;
}