#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasSetSmCountTarget(cublasHandle_t handle, int smCountTarget)
{
	cublasStatus_t retval = cublasSetSmCountTarget(handle, smCountTarget);
	return retval;
}