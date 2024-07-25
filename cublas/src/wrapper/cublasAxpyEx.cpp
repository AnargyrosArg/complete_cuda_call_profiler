#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasAxpyEx(cublasHandle_t handle, int n, const void *alpha, cudaDataType alphaType, const void *x, cudaDataType xType, int incx, void *y, cudaDataType yType, int incy, cudaDataType executiontype)
{
	cublasStatus_t retval = cublasAxpyEx(handle, n, alpha, alphaType, x, xType, incx, y, yType, incy, executiontype);
	return retval;
}