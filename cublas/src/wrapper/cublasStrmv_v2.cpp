#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasStrmv_v2(cublasHandle_t handle, cublasFillMode_t uplo, cublasOperation_t trans, cublasDiagType_t diag, int n, const float *A, int lda, float *x, int incx)
{
	cublasStatus_t retval = cublasStrmv_v2(handle, uplo, trans, diag, n, A, lda, x, incx);
	return retval;
}