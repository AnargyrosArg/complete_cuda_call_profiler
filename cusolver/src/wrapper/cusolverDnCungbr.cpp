#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnCungbr(cusolverDnHandle_t handle, cublasSideMode_t side, int m, int n, int k, cuComplex *A, int lda, const cuComplex *tau, cuComplex *work, int lwork, int *info)
{
	cusolverStatus_t retval = cusolverDnCungbr(handle, side, m, n, k, A, lda, tau, work, lwork, info);
	return retval;
}