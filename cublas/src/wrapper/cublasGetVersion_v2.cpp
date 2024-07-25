#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasGetVersion_v2(cublasHandle_t handle, int *version)
{
	cublasStatus_t retval = cublasGetVersion_v2(handle, version);
	return retval;
}