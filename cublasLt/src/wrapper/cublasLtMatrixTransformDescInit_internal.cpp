#include <cublasLt.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasLtMatrixTransformDescInit_internal(cublasLtMatrixTransformDesc_t transformDesc, size_t size, cudaDataType scaleType)
{
	cublasStatus_t retval = cublasLtMatrixTransformDescInit_internal(transformDesc, size, scaleType);
	return retval;
}