#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasStbmv_v2(cublasHandle_t handle, cublasFillMode_t uplo, cublasOperation_t trans, cublasDiagType_t diag, int n, int k, const float *A, int lda, float *x, int incx)
{
	cublasStatus_t retval = cublasStbmv_v2(handle, uplo, trans, diag, n, k, A, lda, x, incx);
	return retval;
}