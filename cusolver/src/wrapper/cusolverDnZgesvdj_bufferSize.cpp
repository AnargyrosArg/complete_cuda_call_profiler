#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnZgesvdj_bufferSize(cusolverDnHandle_t handle, cusolverEigMode_t jobz, int econ, int m, int n, const cuDoubleComplex *A, int lda, const double *S, const cuDoubleComplex *U, int ldu, const cuDoubleComplex *V, int ldv, int *lwork, gesvdjInfo_t params)
{
	cusolverStatus_t retval = cusolverDnZgesvdj_bufferSize(handle, jobz, econ, m, n, A, lda, S, U, ldu, V, ldv, lwork, params);
	return retval;
}