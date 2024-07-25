#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnDpotrs(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, int nrhs, const double *A, int lda, double *B, int ldb, int *devInfo)
{
	cusolverStatus_t retval = cusolverDnDpotrs(handle, uplo, n, nrhs, A, lda, B, ldb, devInfo);
	return retval;
}