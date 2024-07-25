#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnCungbr_bufferSize(cusolverDnHandle_t handle, cublasSideMode_t side, int m, int n, int k, const cuComplex *A, int lda, const cuComplex *tau, int *lwork)
{
	cusolverStatus_t retval = cusolverDnCungbr_bufferSize(handle, side, m, n, k, A, lda, tau, lwork);
	return retval;
}