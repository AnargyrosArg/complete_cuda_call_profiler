#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseSpMM(cusparseHandle_t handle, cusparseOperation_t opA, cusparseOperation_t opB, const void *alpha, cusparseSpMatDescr_t matA, cusparseDnMatDescr_t matB, const void *beta, cusparseDnMatDescr_t matC, cudaDataType computeType, cusparseSpMMAlg_t alg, void *externalBuffer)
{
	cusparseStatus_t retval = cusparseSpMM(handle, opA, opB, alpha, matA, matB, beta, matC, computeType, alg, externalBuffer);
	return retval;
}