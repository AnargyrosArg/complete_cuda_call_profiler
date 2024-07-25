#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnZungbr_bufferSize(cusolverDnHandle_t handle, cublasSideMode_t side, int m, int n, int k, const cuDoubleComplex *A, int lda, const cuDoubleComplex *tau, int *lwork)
{
	cusolverStatus_t retval = cusolverDnZungbr_bufferSize(handle, side, m, n, k, A, lda, tau, lwork);
	return retval;
}