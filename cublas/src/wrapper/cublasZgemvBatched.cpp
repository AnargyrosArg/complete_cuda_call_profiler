#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasZgemvBatched(cublasHandle_t handle, cublasOperation_t trans, int m, int n, const cuDoubleComplex *alpha, const cuDoubleComplex * const Aarray[], int lda, const cuDoubleComplex * const xarray[], int incx, const cuDoubleComplex *beta, cuDoubleComplex * const yarray[], int incy, int batchCount)
{
	cublasStatus_t retval = cublasZgemvBatched(handle, trans, m, n, alpha, Aarray, lda, xarray, incx, beta, yarray, incy, batchCount);
	return retval;
}