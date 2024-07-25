#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasRotmgEx(cublasHandle_t handle, void *d1, cudaDataType d1Type, void *d2, cudaDataType d2Type, void *x1, cudaDataType x1Type, const void *y1, cudaDataType y1Type, void *param, cudaDataType paramType, cudaDataType executiontype)
{
	cublasStatus_t retval = cublasRotmgEx(handle, d1, d1Type, d2, d2Type, x1, x1Type, y1, y1Type, param, paramType, executiontype);
	return retval;
}