#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasDgemvStridedBatched(cublasHandle_t handle, cublasOperation_t trans, int m, int n, const double *alpha, const double *A, int lda, long long int strideA, const double *x, int incx, long long int stridex, const double *beta, double *y, int incy, long long int stridey, int batchCount)
{
	cublasStatus_t retval = cublasDgemvStridedBatched(handle, trans, m, n, alpha, A, lda, strideA, x, incx, stridex, beta, y, incy, stridey, batchCount);
	return retval;
}