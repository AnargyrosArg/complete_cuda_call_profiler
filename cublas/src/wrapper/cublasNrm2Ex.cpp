#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasNrm2Ex(cublasHandle_t handle, int n, const void *x, cudaDataType xType, int incx, void *result, cudaDataType resultType, cudaDataType executionType)
{
	cublasStatus_t retval = cublasNrm2Ex(handle, n, x, xType, incx, result, resultType, executionType);
	return retval;
}