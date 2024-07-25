#include <cublasLt.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasLtMatmulAlgoCapGetAttribute(const cublasLtMatmulAlgo_t *algo, cublasLtMatmulAlgoCapAttributes_t attr, void *buf, size_t sizeInBytes, size_t *sizeWritten)
{
	cublasStatus_t retval = cublasLtMatmulAlgoCapGetAttribute(algo, attr, buf, sizeInBytes, sizeWritten);
	return retval;
}