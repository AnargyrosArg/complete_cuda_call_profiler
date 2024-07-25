#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseSpVV_bufferSize(cusparseHandle_t handle, cusparseOperation_t opX, cusparseSpVecDescr_t vecX, cusparseDnVecDescr_t vecY, const void *result, cudaDataType computeType, size_t *bufferSize)
{
	cusparseStatus_t retval = cusparseSpVV_bufferSize(handle, opX, vecX, vecY, result, computeType, bufferSize);
	return retval;
}