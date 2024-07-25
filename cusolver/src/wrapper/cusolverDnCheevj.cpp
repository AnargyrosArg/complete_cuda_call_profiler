#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnCheevj(cusolverDnHandle_t handle, cusolverEigMode_t jobz, cublasFillMode_t uplo, int n, cuComplex *A, int lda, float *W, cuComplex *work, int lwork, int *info, syevjInfo_t params)
{
	cusolverStatus_t retval = cusolverDnCheevj(handle, jobz, uplo, n, A, lda, W, work, lwork, info, params);
	return retval;
}