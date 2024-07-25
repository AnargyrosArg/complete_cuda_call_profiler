#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasGetProperty(libraryPropertyType type, int *value)
{
	cublasStatus_t retval = cublasGetProperty(type, value);
	return retval;
}