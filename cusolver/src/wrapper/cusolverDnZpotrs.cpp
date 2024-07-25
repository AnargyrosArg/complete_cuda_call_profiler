#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnZpotrs(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, int nrhs, const cuDoubleComplex *A, int lda, cuDoubleComplex *B, int ldb, int *devInfo)
{
	cusolverStatus_t retval = cusolverDnZpotrs(handle, uplo, n, nrhs, A, lda, B, ldb, devInfo);
	return retval;
}