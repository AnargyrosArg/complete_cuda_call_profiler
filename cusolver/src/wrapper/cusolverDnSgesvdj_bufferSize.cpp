#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnSgesvdj_bufferSize(cusolverDnHandle_t handle, cusolverEigMode_t jobz, int econ, int m, int n, const float *A, int lda, const float *S, const float *U, int ldu, const float *V, int ldv, int *lwork, gesvdjInfo_t params)
{
	cusolverStatus_t retval = cusolverDnSgesvdj_bufferSize(handle, jobz, econ, m, n, A, lda, S, U, ldu, V, ldv, lwork, params);
	return retval;
}