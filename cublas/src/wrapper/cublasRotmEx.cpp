#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasRotmEx(cublasHandle_t handle, int n, void *x, cudaDataType xType, int incx, void *y, cudaDataType yType, int incy, const void *param, cudaDataType paramType, cudaDataType executiontype)
{
	cublasStatus_t retval = cublasRotmEx(handle, n, x, xType, incx, y, yType, incy, param, paramType, executiontype);
	return retval;
}