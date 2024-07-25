#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasRotgEx(cublasHandle_t handle, void *a, void *b, cudaDataType abType, void *c, void *s, cudaDataType csType, cudaDataType executiontype)
{
	cublasStatus_t retval = cublasRotgEx(handle, a, b, abType, c, s, csType, executiontype);
	return retval;
}