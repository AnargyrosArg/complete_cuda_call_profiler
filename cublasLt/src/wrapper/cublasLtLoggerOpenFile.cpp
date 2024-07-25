#include <cublasLt.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasLtLoggerOpenFile(const char *logFile)
{
	cublasStatus_t retval = cublasLtLoggerOpenFile(logFile);
	return retval;
}