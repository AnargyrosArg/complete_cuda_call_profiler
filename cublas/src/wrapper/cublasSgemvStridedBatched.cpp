#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasSgemvStridedBatched(cublasHandle_t handle, cublasOperation_t trans, int m, int n, const float *alpha, const float *A, int lda, long long int strideA, const float *x, int incx, long long int stridex, const float *beta, float *y, int incy, long long int stridey, int batchCount)
{
	cublasStatus_t retval = cublasSgemvStridedBatched(handle, trans, m, n, alpha, A, lda, strideA, x, incx, stridex, beta, y, incy, stridey, batchCount);
	return retval;
}