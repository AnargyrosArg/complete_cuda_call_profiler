#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnDsytrd_bufferSize(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, const double *A, int lda, const double *d, const double *e, const double *tau, int *lwork)
{
	cusolverStatus_t retval = cusolverDnDsytrd_bufferSize(handle, uplo, n, A, lda, d, e, tau, lwork);
	return retval;
}