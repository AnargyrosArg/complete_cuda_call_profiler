#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnCpotri(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, cuComplex *A, int lda, cuComplex *work, int lwork, int *devInfo)
{
	cusolverStatus_t retval = cusolverDnCpotri(handle, uplo, n, A, lda, work, lwork, devInfo);
	return retval;
}