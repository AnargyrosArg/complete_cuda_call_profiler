#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasGetMathMode(cublasHandle_t handle, cublasMath_t *mode)
{
	cublasStatus_t retval = cublasGetMathMode(handle, mode);
	return retval;
}