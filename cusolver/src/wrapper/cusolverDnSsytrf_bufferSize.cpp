#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnSsytrf_bufferSize(cusolverDnHandle_t handle, int n, float *A, int lda, int *lwork)
{
	cusolverStatus_t retval = cusolverDnSsytrf_bufferSize(handle, n, A, lda, lwork);
	return retval;
}