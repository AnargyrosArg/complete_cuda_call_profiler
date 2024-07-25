#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasCdotc_v2(cublasHandle_t handle, int n, const cuComplex *x, int incx, const cuComplex *y, int incy, cuComplex *result)
{
	cublasStatus_t retval = cublasCdotc_v2(handle, n, x, incx, y, incy, result);
	return retval;
}