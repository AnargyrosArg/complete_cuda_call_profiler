#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasSaxpy_v2(cublasHandle_t handle, int n, const float *alpha, const float *x, int incx, float *y, int incy)
{
	cublasStatus_t retval = cublasSaxpy_v2(handle, n, alpha, x, incx, y, incy);
	return retval;
}