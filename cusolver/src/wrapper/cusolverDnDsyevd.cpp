#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnDsyevd(cusolverDnHandle_t handle, cusolverEigMode_t jobz, cublasFillMode_t uplo, int n, double *A, int lda, double *W, double *work, int lwork, int *info)
{
	cusolverStatus_t retval = cusolverDnDsyevd(handle, jobz, uplo, n, A, lda, W, work, lwork, info);
	return retval;
}