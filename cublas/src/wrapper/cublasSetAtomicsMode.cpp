#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasSetAtomicsMode(cublasHandle_t handle, cublasAtomicsMode_t mode)
{
	cublasStatus_t retval = cublasSetAtomicsMode(handle, mode);
	return retval;
}