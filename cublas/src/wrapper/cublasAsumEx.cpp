#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasAsumEx(cublasHandle_t handle, int n, const void *x, cudaDataType xType, int incx, void *result, cudaDataType resultType, cudaDataType executiontype)
{
	cublasStatus_t retval = cublasAsumEx(handle, n, x, xType, incx, result, resultType, executiontype);
	return retval;
}