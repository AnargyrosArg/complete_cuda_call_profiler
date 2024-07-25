#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnCgesvdj(cusolverDnHandle_t handle, cusolverEigMode_t jobz, int econ, int m, int n, cuComplex *A, int lda, float *S, cuComplex *U, int ldu, cuComplex *V, int ldv, cuComplex *work, int lwork, int *info, gesvdjInfo_t params)
{
	cusolverStatus_t retval = cusolverDnCgesvdj(handle, jobz, econ, m, n, A, lda, S, U, ldu, V, ldv, work, lwork, info, params);
	return retval;
}