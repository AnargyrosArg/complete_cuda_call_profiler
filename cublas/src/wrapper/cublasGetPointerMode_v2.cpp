#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasGetPointerMode_v2(cublasHandle_t handle, cublasPointerMode_t *mode)
{
	cublasStatus_t retval = cublasGetPointerMode_v2(handle, mode);
	return retval;
}