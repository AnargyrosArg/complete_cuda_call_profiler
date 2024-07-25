#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasZswap_v2(cublasHandle_t handle, int n, cuDoubleComplex *x, int incx, cuDoubleComplex *y, int incy)
{
	cublasStatus_t retval = cublasZswap_v2(handle, n, x, incx, y, incy);
	return retval;
}