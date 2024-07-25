#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseDenseToSparse_analysis(cusparseHandle_t handle, cusparseDnMatDescr_t matA, cusparseSpMatDescr_t matB, cusparseDenseToSparseAlg_t alg, void *externalBuffer)
{
	cusparseStatus_t retval = cusparseDenseToSparse_analysis(handle, matA, matB, alg, externalBuffer);
	return retval;
}