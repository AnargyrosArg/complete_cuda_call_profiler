#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnDsytrd(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, double *A, int lda, double *d, double *e, double *tau, double *work, int lwork, int *info)
{
	cusolverStatus_t retval = cusolverDnDsytrd(handle, uplo, n, A, lda, d, e, tau, work, lwork, info);
	return retval;
}