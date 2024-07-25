#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasDgemvBatched(cublasHandle_t handle, cublasOperation_t trans, int m, int n, const double *alpha, const double * const Aarray[], int lda, const double * const xarray[], int incx, const double *beta, double * const yarray[], int incy, int batchCount)
{
	cublasStatus_t retval = cublasDgemvBatched(handle, trans, m, n, alpha, Aarray, lda, xarray, incx, beta, yarray, incy, batchCount);
	return retval;
}