#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasSswap_v2(cublasHandle_t handle, int n, float *x, int incx, float *y, int incy)
{
	cublasStatus_t retval = cublasSswap_v2(handle, n, x, incx, y, incy);
	return retval;
}