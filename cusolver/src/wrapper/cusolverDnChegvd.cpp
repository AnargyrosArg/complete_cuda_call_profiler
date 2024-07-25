#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnChegvd(cusolverDnHandle_t handle, cusolverEigType_t itype, cusolverEigMode_t jobz, cublasFillMode_t uplo, int n, cuComplex *A, int lda, cuComplex *B, int ldb, float *W, cuComplex *work, int lwork, int *info)
{
	cusolverStatus_t retval = cusolverDnChegvd(handle, itype, jobz, uplo, n, A, lda, B, ldb, W, work, lwork, info);
	return retval;
}