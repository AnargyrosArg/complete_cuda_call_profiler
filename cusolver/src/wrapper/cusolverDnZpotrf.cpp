#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnZpotrf(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, cuDoubleComplex *A, int lda, cuDoubleComplex *Workspace, int Lwork, int *devInfo)
{
	cusolverStatus_t retval = cusolverDnZpotrf(handle, uplo, n, A, lda, Workspace, Lwork, devInfo);
	return retval;
}