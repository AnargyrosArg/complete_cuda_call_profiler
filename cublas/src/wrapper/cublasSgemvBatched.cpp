#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasSgemvBatched(cublasHandle_t handle, cublasOperation_t trans, int m, int n, const float *alpha, const float * const Aarray[], int lda, const float * const xarray[], int incx, const float *beta, float * const yarray[], int incy, int batchCount)
{
	cublasStatus_t retval = cublasSgemvBatched(handle, trans, m, n, alpha, Aarray, lda, xarray, incx, beta, yarray, incy, batchCount);
	return retval;
}