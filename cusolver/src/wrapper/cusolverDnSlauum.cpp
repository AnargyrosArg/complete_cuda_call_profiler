#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnSlauum(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, float *A, int lda, float *work, int lwork, int *devInfo)
{
	cusolverStatus_t retval = cusolverDnSlauum(handle, uplo, n, A, lda, work, lwork, devInfo);
	return retval;
}