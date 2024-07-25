#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasCgemvBatched(cublasHandle_t handle, cublasOperation_t trans, int m, int n, const cuComplex *alpha, const cuComplex * const Aarray[], int lda, const cuComplex * const xarray[], int incx, const cuComplex *beta, cuComplex * const yarray[], int incy, int batchCount)
{
	cublasStatus_t retval = cublasCgemvBatched(handle, trans, m, n, alpha, Aarray, lda, xarray, incx, beta, yarray, incy, batchCount);
	return retval;
}