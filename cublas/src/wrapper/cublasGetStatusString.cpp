#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
const char * wrapper_cublasGetStatusString(cublasStatus_t status)
{
	const char * retval = cublasGetStatusString(status);
	return retval;
}