#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
size_t wrapper_cublasGetCudartVersion()
{
	size_t retval = cublasGetCudartVersion();
	return retval;
}