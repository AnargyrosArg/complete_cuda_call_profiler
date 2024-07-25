#include <cublasLt.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasLtMatrixTransformDescDestroy(cublasLtMatrixTransformDesc_t transformDesc)
{
	cublasStatus_t retval = cublasLtMatrixTransformDescDestroy(transformDesc);
	return retval;
}