#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnDorgtr_bufferSize(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, const double *A, int lda, const double *tau, int *lwork)
{
	cusolverStatus_t retval = cusolverDnDorgtr_bufferSize(handle, uplo, n, A, lda, tau, lwork);
	return retval;
}