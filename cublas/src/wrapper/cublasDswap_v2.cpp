#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasDswap_v2(cublasHandle_t handle, int n, double *x, int incx, double *y, int incy)
{
	cublasStatus_t retval = cublasDswap_v2(handle, n, x, incx, y, incy);
	return retval;
}