#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasGetSmCountTarget(cublasHandle_t handle, int *smCountTarget)
{
	cublasStatus_t retval = cublasGetSmCountTarget(handle, smCountTarget);
	return retval;
}