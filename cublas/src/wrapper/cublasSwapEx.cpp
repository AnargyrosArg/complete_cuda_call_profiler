#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasSwapEx(cublasHandle_t handle, int n, void *x, cudaDataType xType, int incx, void *y, cudaDataType yType, int incy)
{
	cublasStatus_t retval = cublasSwapEx(handle, n, x, xType, incx, y, yType, incy);
	return retval;
}