#include <cublasLt.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasLtCreate(cublasLtHandle_t *lightHandle)
{
	cublasStatus_t retval = cublasLtCreate(lightHandle);
	return retval;
}