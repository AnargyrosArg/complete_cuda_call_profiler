#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseConstrainedGeMM(cusparseHandle_t handle, cusparseOperation_t opA, cusparseOperation_t opB, const void *alpha, cusparseDnMatDescr_t matA, cusparseDnMatDescr_t matB, const void *beta, cusparseSpMatDescr_t matC, cudaDataType computeType, void *externalBuffer)
{
	cusparseStatus_t retval = cusparseConstrainedGeMM(handle, opA, opB, alpha, matA, matB, beta, matC, computeType, externalBuffer);
	return retval;
}