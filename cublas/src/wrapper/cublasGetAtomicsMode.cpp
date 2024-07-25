#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasGetAtomicsMode(cublasHandle_t handle, cublasAtomicsMode_t *mode)
{
	cublasStatus_t retval = cublasGetAtomicsMode(handle, mode);
	return retval;
}