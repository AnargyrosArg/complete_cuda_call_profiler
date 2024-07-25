#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasShutdown()
{
	cublasStatus_t retval = cublasShutdown();
	return retval;
}