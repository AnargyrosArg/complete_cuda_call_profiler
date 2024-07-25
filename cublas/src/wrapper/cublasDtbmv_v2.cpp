#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasDtbmv_v2(cublasHandle_t handle, cublasFillMode_t uplo, cublasOperation_t trans, cublasDiagType_t diag, int n, int k, const double *A, int lda, double *x, int incx)
{
	cublasStatus_t retval = cublasDtbmv_v2(handle, uplo, trans, diag, n, k, A, lda, x, incx);
	return retval;
}