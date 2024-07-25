#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasIaminEx(cublasHandle_t handle, int n, const void *x, cudaDataType xType, int incx, int *result)
{
	cublasStatus_t retval = cublasIaminEx(handle, n, x, xType, incx, result);
	return retval;
}