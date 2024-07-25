#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasChpmv_v2(cublasHandle_t handle, cublasFillMode_t uplo, int n, const cuComplex *alpha, const cuComplex *AP, const cuComplex *x, int incx, const cuComplex *beta, cuComplex *y, int incy)
{
	cublasStatus_t retval = cublasChpmv_v2(handle, uplo, n, alpha, AP, x, incx, beta, y, incy);
	return retval;
}