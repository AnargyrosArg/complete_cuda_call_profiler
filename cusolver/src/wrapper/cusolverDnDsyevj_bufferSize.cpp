#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnDsyevj_bufferSize(cusolverDnHandle_t handle, cusolverEigMode_t jobz, cublasFillMode_t uplo, int n, const double *A, int lda, const double *W, int *lwork, syevjInfo_t params)
{
	cusolverStatus_t retval = cusolverDnDsyevj_bufferSize(handle, jobz, uplo, n, A, lda, W, lwork, params);
	return retval;
}