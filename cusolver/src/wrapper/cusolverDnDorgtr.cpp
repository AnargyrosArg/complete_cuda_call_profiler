#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnDorgtr(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, double *A, int lda, const double *tau, double *work, int lwork, int *info)
{
	cusolverStatus_t retval = cusolverDnDorgtr(handle, uplo, n, A, lda, tau, work, lwork, info);
	return retval;
}