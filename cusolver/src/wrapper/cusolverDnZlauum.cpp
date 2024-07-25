#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnZlauum(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, cuDoubleComplex *A, int lda, cuDoubleComplex *work, int lwork, int *devInfo)
{
	cusolverStatus_t retval = cusolverDnZlauum(handle, uplo, n, A, lda, work, lwork, devInfo);
	return retval;
}