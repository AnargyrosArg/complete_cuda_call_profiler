#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnChetrd(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, cuComplex *A, int lda, float *d, float *e, cuComplex *tau, cuComplex *work, int lwork, int *info)
{
	cusolverStatus_t retval = cusolverDnChetrd(handle, uplo, n, A, lda, d, e, tau, work, lwork, info);
	return retval;
}