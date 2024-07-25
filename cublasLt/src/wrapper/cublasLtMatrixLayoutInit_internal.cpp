#include <cublasLt.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasLtMatrixLayoutInit_internal(cublasLtMatrixLayout_t matLayout, size_t size, cudaDataType type, uint64_t rows, uint64_t cols, int64_t ld)
{
	cublasStatus_t retval = cublasLtMatrixLayoutInit_internal(matLayout, size, type, rows, cols, ld);
	return retval;
}