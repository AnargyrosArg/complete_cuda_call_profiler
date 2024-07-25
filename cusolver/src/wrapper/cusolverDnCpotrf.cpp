#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnCpotrf(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, cuComplex *A, int lda, cuComplex *Workspace, int Lwork, int *devInfo)
{
	cusolverStatus_t retval = cusolverDnCpotrf(handle, uplo, n, A, lda, Workspace, Lwork, devInfo);
	return retval;
}