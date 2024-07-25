#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasCswap_v2(cublasHandle_t handle, int n, cuComplex *x, int incx, cuComplex *y, int incy)
{
	cublasStatus_t retval = cublasCswap_v2(handle, n, x, incx, y, incy);
	return retval;
}