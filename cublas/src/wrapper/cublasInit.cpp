#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasInit()
{
	cublasStatus_t retval = cublasInit();
	return retval;
}