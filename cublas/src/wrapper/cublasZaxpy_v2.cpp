#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasZaxpy_v2(cublasHandle_t handle, int n, const cuDoubleComplex *alpha, const cuDoubleComplex *x, int incx, cuDoubleComplex *y, int incy)
{
	cublasStatus_t retval = cublasZaxpy_v2(handle, n, alpha, x, incx, y, incy);
	return retval;
}