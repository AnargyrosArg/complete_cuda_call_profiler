#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasCgeru_v2(cublasHandle_t handle, int m, int n, const cuComplex *alpha, const cuComplex *x, int incx, const cuComplex *y, int incy, cuComplex *A, int lda)
{
	cublasStatus_t retval = cublasCgeru_v2(handle, m, n, alpha, x, incx, y, incy, A, lda);
	return retval;
}