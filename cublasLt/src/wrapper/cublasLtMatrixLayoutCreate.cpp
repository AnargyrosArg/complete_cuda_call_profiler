#include <cublasLt.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasLtMatrixLayoutCreate(cublasLtMatrixLayout_t *matLayout, cudaDataType type, uint64_t rows, uint64_t cols, int64_t ld)
{
	cublasStatus_t retval = cublasLtMatrixLayoutCreate(matLayout, type, rows, cols, ld);
	return retval;
}