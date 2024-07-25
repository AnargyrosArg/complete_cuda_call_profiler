#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasGetVersion(int *version)
{
	cublasStatus_t retval = cublasGetVersion(version);
	return retval;
}