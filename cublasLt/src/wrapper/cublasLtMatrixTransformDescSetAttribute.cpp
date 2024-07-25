#include <cublasLt.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasLtMatrixTransformDescSetAttribute(cublasLtMatrixTransformDesc_t transformDesc, cublasLtMatrixTransformDescAttributes_t attr, const void *buf, size_t sizeInBytes)
{
	cublasStatus_t retval = cublasLtMatrixTransformDescSetAttribute(transformDesc, attr, buf, sizeInBytes);
	return retval;
}