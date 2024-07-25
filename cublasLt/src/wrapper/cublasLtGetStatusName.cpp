#include <cublasLt.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
const char * wrapper_cublasLtGetStatusName(cublasStatus_t status)
{
	const char * retval = cublasLtGetStatusName(status);
	return retval;
}