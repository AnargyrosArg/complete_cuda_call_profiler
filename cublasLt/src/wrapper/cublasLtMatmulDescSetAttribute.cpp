#include <cublasLt.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasLtMatmulDescSetAttribute(cublasLtMatmulDesc_t matmulDesc, cublasLtMatmulDescAttributes_t attr, const void *buf, size_t sizeInBytes)
{
	cublasStatus_t retval = cublasLtMatmulDescSetAttribute(matmulDesc, attr, buf, sizeInBytes);
	return retval;
}