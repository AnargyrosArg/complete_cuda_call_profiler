#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasCgemvStridedBatched(cublasHandle_t handle, cublasOperation_t trans, int m, int n, const cuComplex *alpha, const cuComplex *A, int lda, long long int strideA, const cuComplex *x, int incx, long long int stridex, const cuComplex *beta, cuComplex *y, int incy, long long int stridey, int batchCount)
{
	cublasStatus_t retval = cublasCgemvStridedBatched(handle, trans, m, n, alpha, A, lda, strideA, x, incx, stridex, beta, y, incy, stridey, batchCount);
	return retval;
}