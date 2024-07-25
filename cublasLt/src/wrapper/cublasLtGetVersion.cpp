#include <cublasLt.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
size_t wrapper_cublasLtGetVersion()
{
	size_t retval = cublasLtGetVersion();
	return retval;
}