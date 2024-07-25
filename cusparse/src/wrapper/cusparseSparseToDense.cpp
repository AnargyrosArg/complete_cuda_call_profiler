#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseSparseToDense(cusparseHandle_t handle, cusparseSpMatDescr_t matA, cusparseDnMatDescr_t matB, cusparseSparseToDenseAlg_t alg, void *externalBuffer)
{
	cusparseStatus_t retval = cusparseSparseToDense(handle, matA, matB, alg, externalBuffer);
	return retval;
}