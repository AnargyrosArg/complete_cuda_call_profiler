#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnCpotrs(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, int nrhs, const cuComplex *A, int lda, cuComplex *B, int ldb, int *devInfo)
{
	cusolverStatus_t retval = cusolverDnCpotrs(handle, uplo, n, nrhs, A, lda, B, ldb, devInfo);
	return retval;
}