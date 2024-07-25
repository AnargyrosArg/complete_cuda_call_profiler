#include <cublasLt.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasLtLoggerSetLevel(int level)
{
	cublasStatus_t retval = cublasLtLoggerSetLevel(level);
	return retval;
}