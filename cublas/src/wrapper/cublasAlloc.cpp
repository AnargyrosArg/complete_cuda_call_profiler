#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasAlloc(int n, int elemSize, void **devicePtr)
{
	cublasStatus_t retval = cublasAlloc(n, elemSize, devicePtr);
	return retval;
}