#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnDpotri(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, double *A, int lda, double *work, int lwork, int *devInfo)
{
	cusolverStatus_t retval = cusolverDnDpotri(handle, uplo, n, A, lda, work, lwork, devInfo);
	return retval;
}