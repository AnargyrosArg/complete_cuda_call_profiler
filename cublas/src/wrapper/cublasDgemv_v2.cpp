#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasDgemv_v2(cublasHandle_t handle, cublasOperation_t trans, int m, int n, const double *alpha, const double *A, int lda, const double *x, int incx, const double *beta, double *y, int incy)
{
	cublasStatus_t retval = cublasDgemv_v2(handle, trans, m, n, alpha, A, lda, x, incx, beta, y, incy);
	return retval;
}