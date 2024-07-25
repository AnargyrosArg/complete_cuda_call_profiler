#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasSetMathMode(cublasHandle_t handle, cublasMath_t mode)
{
	cublasStatus_t retval = cublasSetMathMode(handle, mode);
	return retval;
}