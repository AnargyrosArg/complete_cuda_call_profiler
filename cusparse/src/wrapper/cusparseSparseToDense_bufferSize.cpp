#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseSparseToDense_bufferSize(cusparseHandle_t handle, cusparseSpMatDescr_t matA, cusparseDnMatDescr_t matB, cusparseSparseToDenseAlg_t alg, size_t *bufferSize)
{
	cusparseStatus_t retval = cusparseSparseToDense_bufferSize(handle, matA, matB, alg, bufferSize);
	return retval;
}