#include <cublasLt.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasLtLoggerForceDisable()
{
	cublasStatus_t retval = cublasLtLoggerForceDisable();
	return retval;
}