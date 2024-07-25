#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasCdotu_v2(cublasHandle_t handle, int n, const cuComplex *x, int incx, const cuComplex *y, int incy, cuComplex *result)
{
	cublasStatus_t retval = cublasCdotu_v2(handle, n, x, incx, y, incy, result);
	return retval;
}