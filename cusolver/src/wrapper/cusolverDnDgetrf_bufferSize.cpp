#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnDgetrf_bufferSize(cusolverDnHandle_t handle, int m, int n, double *A, int lda, int *Lwork)
{
	cusolverStatus_t retval = cusolverDnDgetrf_bufferSize(handle, m, n, A, lda, Lwork);
	return retval;
}