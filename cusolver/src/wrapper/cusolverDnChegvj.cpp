#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnChegvj(cusolverDnHandle_t handle, cusolverEigType_t itype, cusolverEigMode_t jobz, cublasFillMode_t uplo, int n, cuComplex *A, int lda, cuComplex *B, int ldb, float *W, cuComplex *work, int lwork, int *info, syevjInfo_t params)
{
	cusolverStatus_t retval = cusolverDnChegvj(handle, itype, jobz, uplo, n, A, lda, B, ldb, W, work, lwork, info, params);
	return retval;
}