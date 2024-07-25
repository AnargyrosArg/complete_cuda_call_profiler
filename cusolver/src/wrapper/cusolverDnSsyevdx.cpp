#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnSsyevdx(cusolverDnHandle_t handle, cusolverEigMode_t jobz, cusolverEigRange_t range, cublasFillMode_t uplo, int n, float *A, int lda, float vl, float vu, int il, int iu, int *meig, float *W, float *work, int lwork, int *info)
{
	cusolverStatus_t retval = cusolverDnSsyevdx(handle, jobz, range, uplo, n, A, lda, vl, vu, il, iu, meig, W, work, lwork, info);
	return retval;
}