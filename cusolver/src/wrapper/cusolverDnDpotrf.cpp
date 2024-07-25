#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnDpotrf(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, double *A, int lda, double *Workspace, int Lwork, int *devInfo)
{
	cusolverStatus_t retval = cusolverDnDpotrf(handle, uplo, n, A, lda, Workspace, Lwork, devInfo);
	return retval;
}