#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnDgeqrf_bufferSize(cusolverDnHandle_t handle, int m, int n, double *A, int lda, int *lwork)
{
	cusolverStatus_t retval = cusolverDnDgeqrf_bufferSize(handle, m, n, A, lda, lwork);
	return retval;
}