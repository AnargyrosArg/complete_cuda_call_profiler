#include <cublasLt.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
size_t wrapper_cublasLtGetCudartVersion()
{
	size_t retval = cublasLtGetCudartVersion();
	return retval;
}