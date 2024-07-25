#include <cublasLt.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasLtGetProperty(libraryPropertyType type, int *value)
{
	cublasStatus_t retval = cublasLtGetProperty(type, value);
	return retval;
}