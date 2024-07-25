#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnSsyevj(cusolverDnHandle_t handle, cusolverEigMode_t jobz, cublasFillMode_t uplo, int n, float *A, int lda, float *W, float *work, int lwork, int *info, syevjInfo_t params)
{
	cusolverStatus_t retval = cusolverDnSsyevj(handle, jobz, uplo, n, A, lda, W, work, lwork, info, params);
	return retval;
}