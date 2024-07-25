#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasDotcEx(cublasHandle_t handle, int n, const void *x, cudaDataType xType, int incx, const void *y, cudaDataType yType, int incy, void *result, cudaDataType resultType, cudaDataType executionType)
{
	cublasStatus_t retval = cublasDotcEx(handle, n, x, xType, incx, y, yType, incy, result, resultType, executionType);
	return retval;
}