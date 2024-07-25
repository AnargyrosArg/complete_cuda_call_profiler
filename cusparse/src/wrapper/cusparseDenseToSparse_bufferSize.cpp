#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseDenseToSparse_bufferSize(cusparseHandle_t handle, cusparseDnMatDescr_t matA, cusparseSpMatDescr_t matB, cusparseDenseToSparseAlg_t alg, size_t *bufferSize)
{
	cusparseStatus_t retval = cusparseDenseToSparse_bufferSize(handle, matA, matB, alg, bufferSize);
	return retval;
}