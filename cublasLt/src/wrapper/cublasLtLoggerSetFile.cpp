#include <cublasLt.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasLtLoggerSetFile(FILE *file)
{
	cublasStatus_t retval = cublasLtLoggerSetFile(file);
	return retval;
}