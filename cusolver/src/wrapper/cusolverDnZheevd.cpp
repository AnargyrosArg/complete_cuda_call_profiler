#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnZheevd(cusolverDnHandle_t handle, cusolverEigMode_t jobz, cublasFillMode_t uplo, int n, cuDoubleComplex *A, int lda, double *W, cuDoubleComplex *work, int lwork, int *info)
{
	cusolverStatus_t retval = cusolverDnZheevd(handle, jobz, uplo, n, A, lda, W, work, lwork, info);
	return retval;
}