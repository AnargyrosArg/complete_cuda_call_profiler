#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasDtrmv_v2(cublasHandle_t handle, cublasFillMode_t uplo, cublasOperation_t trans, cublasDiagType_t diag, int n, const double *A, int lda, double *x, int incx)
{
	cublasStatus_t retval = cublasDtrmv_v2(handle, uplo, trans, diag, n, A, lda, x, incx);
	return retval;
}