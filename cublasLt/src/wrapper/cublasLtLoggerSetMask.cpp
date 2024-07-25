#include <cublasLt.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasLtLoggerSetMask(int mask)
{
	cublasStatus_t retval = cublasLtLoggerSetMask(mask);
	return retval;
}