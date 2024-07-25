#include <cublasLt.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasLtMatmulDescGetAttribute(cublasLtMatmulDesc_t matmulDesc, cublasLtMatmulDescAttributes_t attr, void *buf, size_t sizeInBytes, size_t *sizeWritten)
{
	cublasStatus_t retval = cublasLtMatmulDescGetAttribute(matmulDesc, attr, buf, sizeInBytes, sizeWritten);
	return retval;
}