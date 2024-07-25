#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasDaxpy_v2(cublasHandle_t handle, int n, const double *alpha, const double *x, int incx, double *y, int incy)
{
	cublasStatus_t retval = cublasDaxpy_v2(handle, n, alpha, x, incx, y, incy);
	return retval;
}