#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasRotEx(cublasHandle_t handle, int n, void *x, cudaDataType xType, int incx, void *y, cudaDataType yType, int incy, const void *c, const void *s, cudaDataType csType, cudaDataType executiontype)
{
	cublasStatus_t retval = cublasRotEx(handle, n, x, xType, incx, y, yType, incy, c, s, csType, executiontype);
	return retval;
}