#include <cublasLt.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasLtMatrixLayoutDestroy(cublasLtMatrixLayout_t matLayout)
{
	cublasStatus_t retval = cublasLtMatrixLayoutDestroy(matLayout);
	return retval;
}