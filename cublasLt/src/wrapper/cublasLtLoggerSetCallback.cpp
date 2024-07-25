#include <cublasLt.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasLtLoggerSetCallback(cublasLtLoggerCallback_t callback)
{
	cublasStatus_t retval = cublasLtLoggerSetCallback(callback);
	return retval;
}