#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnZhegvj(cusolverDnHandle_t handle, cusolverEigType_t itype, cusolverEigMode_t jobz, cublasFillMode_t uplo, int n, cuDoubleComplex *A, int lda, cuDoubleComplex *B, int ldb, double *W, cuDoubleComplex *work, int lwork, int *info, syevjInfo_t params)
{
	cusolverStatus_t retval = cusolverDnZhegvj(handle, itype, jobz, uplo, n, A, lda, B, ldb, W, work, lwork, info, params);
	return retval;
}