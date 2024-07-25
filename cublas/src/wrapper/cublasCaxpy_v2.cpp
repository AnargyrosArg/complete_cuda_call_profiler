#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasCaxpy_v2(cublasHandle_t handle, int n, const cuComplex *alpha, const cuComplex *x, int incx, cuComplex *y, int incy)
{
	cublasStatus_t retval = cublasCaxpy_v2(handle, n, alpha, x, incx, y, incy);
	return retval;
}