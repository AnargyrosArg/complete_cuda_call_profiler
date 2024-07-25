#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasScalEx(cublasHandle_t handle, int n, const void *alpha, cudaDataType alphaType, void *x, cudaDataType xType, int incx, cudaDataType executionType)
{
	cublasStatus_t retval = cublasScalEx(handle, n, alpha, alphaType, x, xType, incx, executionType);
	return retval;
}