#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnSpotrf(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, float *A, int lda, float *Workspace, int Lwork, int *devInfo)
{
	cusolverStatus_t retval = cusolverDnSpotrf(handle, uplo, n, A, lda, Workspace, Lwork, devInfo);
	return retval;
}