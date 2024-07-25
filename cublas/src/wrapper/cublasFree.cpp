#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasFree(void *devicePtr)
{
	cublasStatus_t retval = cublasFree(devicePtr);
	return retval;
}