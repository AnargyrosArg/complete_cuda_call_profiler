#include <cublasLt.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasLtMatmulDescInit_internal(cublasLtMatmulDesc_t matmulDesc, size_t size, cublasComputeType_t computeType, cudaDataType_t scaleType)
{
	cublasStatus_t retval = cublasLtMatmulDescInit_internal(matmulDesc, size, computeType, scaleType);
	return retval;
}