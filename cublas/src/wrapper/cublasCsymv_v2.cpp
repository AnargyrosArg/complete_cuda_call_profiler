#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasCsymv_v2(cublasHandle_t handle, cublasFillMode_t uplo, int n, const cuComplex *alpha, const cuComplex *A, int lda, const cuComplex *x, int incx, const cuComplex *beta, cuComplex *y, int incy)
{
	cublasStatus_t retval = cublasCsymv_v2(handle, uplo, n, alpha, A, lda, x, incx, beta, y, incy);
	return retval;
}