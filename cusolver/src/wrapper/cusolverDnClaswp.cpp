#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnClaswp(cusolverDnHandle_t handle, int n, cuComplex *A, int lda, int k1, int k2, const int *devIpiv, int incx)
{
	cusolverStatus_t retval = cusolverDnClaswp(handle, n, A, lda, k1, k2, devIpiv, incx);
	return retval;
}