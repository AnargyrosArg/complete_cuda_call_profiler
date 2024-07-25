#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseSpVV(cusparseHandle_t handle, cusparseOperation_t opX, cusparseSpVecDescr_t vecX, cusparseDnVecDescr_t vecY, void *result, cudaDataType computeType, void *externalBuffer)
{
	cusparseStatus_t retval = cusparseSpVV(handle, opX, vecX, vecY, result, computeType, externalBuffer);
	return retval;
}