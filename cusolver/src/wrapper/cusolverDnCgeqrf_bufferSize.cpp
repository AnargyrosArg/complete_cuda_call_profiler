#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnCgeqrf_bufferSize(cusolverDnHandle_t handle, int m, int n, cuComplex *A, int lda, int *lwork)
{
	cusolverStatus_t retval = cusolverDnCgeqrf_bufferSize(handle, m, n, A, lda, lwork);
	return retval;
}