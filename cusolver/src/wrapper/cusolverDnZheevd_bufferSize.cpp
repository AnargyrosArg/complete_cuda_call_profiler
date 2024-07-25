#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnZheevd_bufferSize(cusolverDnHandle_t handle, cusolverEigMode_t jobz, cublasFillMode_t uplo, int n, const cuDoubleComplex *A, int lda, const double *W, int *lwork)
{
	cusolverStatus_t retval = cusolverDnZheevd_bufferSize(handle, jobz, uplo, n, A, lda, W, lwork);
	return retval;
}