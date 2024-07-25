#include <cublasLt.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasLtMatrixLayoutSetAttribute(cublasLtMatrixLayout_t matLayout, cublasLtMatrixLayoutAttribute_t attr, const void *buf, size_t sizeInBytes)
{
	cublasStatus_t retval = cublasLtMatrixLayoutSetAttribute(matLayout, attr, buf, sizeInBytes);
	return retval;
}