#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnDsygvd(cusolverDnHandle_t handle, cusolverEigType_t itype, cusolverEigMode_t jobz, cublasFillMode_t uplo, int n, double *A, int lda, double *B, int ldb, double *W, double *work, int lwork, int *info)
{
	cusolverStatus_t retval = cusolverDnDsygvd(handle, itype, jobz, uplo, n, A, lda, B, ldb, W, work, lwork, info);
	return retval;
}