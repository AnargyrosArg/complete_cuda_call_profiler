#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnDorgbr_bufferSize(cusolverDnHandle_t handle, cublasSideMode_t side, int m, int n, int k, const double *A, int lda, const double *tau, int *lwork)
{
	cusolverStatus_t retval = cusolverDnDorgbr_bufferSize(handle, side, m, n, k, A, lda, tau, lwork);
	return retval;
}