#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnZsytrf_bufferSize(cusolverDnHandle_t handle, int n, cuDoubleComplex *A, int lda, int *lwork)
{
	cusolverStatus_t retval = cusolverDnZsytrf_bufferSize(handle, n, A, lda, lwork);
	return retval;
}