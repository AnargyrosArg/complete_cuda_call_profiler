#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnDsytrf_bufferSize(cusolverDnHandle_t handle, int n, double *A, int lda, int *lwork)
{
	cusolverStatus_t retval = cusolverDnDsytrf_bufferSize(handle, n, A, lda, lwork);
	return retval;
}