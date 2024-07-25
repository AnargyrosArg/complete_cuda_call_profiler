#include <cublasLt.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasLtMatmulAlgoConfigGetAttribute(const cublasLtMatmulAlgo_t *algo, cublasLtMatmulAlgoConfigAttributes_t attr, void *buf, size_t sizeInBytes, size_t *sizeWritten)
{
	cublasStatus_t retval = cublasLtMatmulAlgoConfigGetAttribute(algo, attr, buf, sizeInBytes, sizeWritten);
	return retval;
}