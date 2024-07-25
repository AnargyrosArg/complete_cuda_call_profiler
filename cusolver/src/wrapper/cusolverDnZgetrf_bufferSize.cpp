#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnZgetrf_bufferSize(cusolverDnHandle_t handle, int m, int n, cuDoubleComplex *A, int lda, int *Lwork)
{
	cusolverStatus_t retval = cusolverDnZgetrf_bufferSize(handle, m, n, A, lda, Lwork);
	return retval;
}