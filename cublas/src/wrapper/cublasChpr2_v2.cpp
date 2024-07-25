#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasChpr2_v2(cublasHandle_t handle, cublasFillMode_t uplo, int n, const cuComplex *alpha, const cuComplex *x, int incx, const cuComplex *y, int incy, cuComplex *AP)
{
	cublasStatus_t retval = cublasChpr2_v2(handle, uplo, n, alpha, x, incx, y, incy, AP);
	return retval;
}