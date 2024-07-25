#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasGetError()
{
	cublasStatus_t retval = cublasGetError();
	return retval;
}