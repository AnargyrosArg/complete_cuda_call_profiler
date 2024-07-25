#include <cublasLt.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasLtMatmulAlgoConfigSetAttribute(cublasLtMatmulAlgo_t *algo, cublasLtMatmulAlgoConfigAttributes_t attr, const void *buf, size_t sizeInBytes)
{
	cublasStatus_t retval = cublasLtMatmulAlgoConfigSetAttribute(algo, attr, buf, sizeInBytes);
	return retval;
}