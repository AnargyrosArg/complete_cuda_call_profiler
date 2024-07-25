#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnSorgbr_bufferSize(cusolverDnHandle_t handle, cublasSideMode_t side, int m, int n, int k, const float *A, int lda, const float *tau, int *lwork)
{
	cusolverStatus_t retval = cusolverDnSorgbr_bufferSize(handle, side, m, n, k, A, lda, tau, lwork);
	return retval;
}