#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasSgemv_v2(cublasHandle_t handle, cublasOperation_t trans, int m, int n, const float *alpha, const float *A, int lda, const float *x, int incx, const float *beta, float *y, int incy)
{
	cublasStatus_t retval = cublasSgemv_v2(handle, trans, m, n, alpha, A, lda, x, incx, beta, y, incy);
	return retval;
}