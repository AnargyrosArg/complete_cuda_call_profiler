#include <cublasLt.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasLtMatmulDescCreate(cublasLtMatmulDesc_t *matmulDesc, cublasComputeType_t computeType, cudaDataType_t scaleType)
{
	cublasStatus_t retval = cublasLtMatmulDescCreate(matmulDesc, computeType, scaleType);
	return retval;
}