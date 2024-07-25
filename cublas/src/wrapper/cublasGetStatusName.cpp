#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
const char * wrapper_cublasGetStatusName(cublasStatus_t status)
{
	const char * retval = cublasGetStatusName(status);
	return retval;
}