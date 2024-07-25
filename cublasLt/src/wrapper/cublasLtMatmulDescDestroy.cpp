#include <cublasLt.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasLtMatmulDescDestroy(cublasLtMatmulDesc_t matmulDesc)
{
	cublasStatus_t retval = cublasLtMatmulDescDestroy(matmulDesc);
	return retval;
}