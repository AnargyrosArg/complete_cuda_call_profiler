#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnDpotrf_bufferSize(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, double *A, int lda, int *Lwork)
{
	cusolverStatus_t retval = cusolverDnDpotrf_bufferSize(handle, uplo, n, A, lda, Lwork);
	return retval;
}