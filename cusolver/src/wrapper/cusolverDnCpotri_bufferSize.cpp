#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnCpotri_bufferSize(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, cuComplex *A, int lda, int *lwork)
{
	cusolverStatus_t retval = cusolverDnCpotri_bufferSize(handle, uplo, n, A, lda, lwork);
	return retval;
}