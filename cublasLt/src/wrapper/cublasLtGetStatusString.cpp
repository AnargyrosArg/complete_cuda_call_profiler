#include <cublasLt.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
const char * wrapper_cublasLtGetStatusString(cublasStatus_t status)
{
	const char * retval = cublasLtGetStatusString(status);
	return retval;
}